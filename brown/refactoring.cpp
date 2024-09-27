#include "xml.h"
#include "json.h"

#include "test_runner.h"

#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>

Json::Document XmlToJson(const Xml::Document& doc) {
  using std::vector;
  using std::string;

  vector<Json::Node> result;

  for (const Xml::Node& n : doc.GetRoot().Children()) {
    result.push_back(Json::Node({
      {"category", Json::Node(n.AttributeValue<string>("category"))},
      {"amount", Json::Node(n.AttributeValue<int>("amount"))}
    }));
  }

  return Json::Document(Json::Node(result));
}

Xml::Document JsonToXml(const Json::Document& doc, std::string root_name) {
  using std::vector;
  using std::string;
  using std::unordered_map;

  Xml::Node xml_root(root_name, {});

  for (const Json::Node& n : doc.GetRoot().AsArray()) {
    xml_root.AddChild(Xml::Node("spend", {
      {"category", n.AsMap().at("category").AsString()},
      {"amount", std::to_string(n.AsMap().at("amount").AsInt())}
    }));
  }

  return Xml::Document(xml_root);
}

void TestXmlToJson() {
  using std::vector;
  using std::string;
  using std::stringstream;

  Xml::Node root("july", {});
  root.AddChild({"spend", {{"category", "travel"}, {"amount", "23400"}}});
  root.AddChild({"spend", {{"category", "food"}, {"amount", "5000"}}});
  root.AddChild({"spend", {{"category", "transport"}, {"amount", "1150"}}});
  root.AddChild({"spend", {{"category", "sport"}, {"amount", "12000"}}});
  const Xml::Document xml_doc(std::move(root));

  Json::Document json_doc = XmlToJson(xml_doc);

  const auto& items = json_doc.GetRoot().AsArray();
  ASSERT_EQUAL(items.size(), 4u);

  const vector<string> expected_category = {"travel", "food", "transport", "sport"};
  const vector<int> expected_amount = {23400, 5000, 1150, 12000};

  for (size_t i = 0; i < items.size(); ++i) {
    const auto& item = items[i].AsMap();

    stringstream ss;
    ss << "i = " << i;

    AssertEqual(item.at("category").AsString(), expected_category[i], ss.str());
    AssertEqual(item.at("amount").AsInt(), expected_amount[i], ss.str());
  }
}

void TestJsonToXml() {
  using std::vector;
  using std::string;
  using std::map;

  std::istringstream json_input(R"([
    {"amount": 2500, "category": "food"},
    {"amount": 1150, "category": "transport"},
    {"amount": 5780, "category": "restaurants"},
    {"amount": 7500, "category": "clothes"},
    {"amount": 23740, "category": "travel"},
    {"amount": 12000, "category": "sport"}
  ])");

  const Json::Document json_doc = Json::Load(json_input);

  string root_name = "month";
  const Xml::Document xml_doc = JsonToXml(json_doc, root_name);

  const vector<Xml::Node>& children = xml_doc.GetRoot().Children();
  ASSERT_EQUAL(xml_doc.GetRoot().Name(), root_name);
  ASSERT_EQUAL(children.size(), 6u);

  const vector<string> expected_category = {
    "food", "transport", "restaurants", "clothes", "travel", "sport"
  };
  const vector<int> expected_amount = {2500, 1150, 5780, 7500, 23740, 12000};

  for (size_t i = 0; i < children.size(); ++i) {
    const Xml::Node& c = children[i];

    std::stringstream ss;
    ss << "i = " << i;

    AssertEqual(c.Name(), "spend", ss.str());
    AssertEqual(c.AttributeValue<string>("category"), expected_category[i], ss.str());
    AssertEqual(c.AttributeValue<int>("amount"), expected_amount[i], ss.str());
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestXmlToJson);
  RUN_TEST(tr, TestJsonToXml);
  return 0;
}
