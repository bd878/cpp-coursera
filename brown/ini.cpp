#include "ini.h"

pair<string_view, string_view> Ini::Split(string_view line, char by) {
  size_t pos = line.find(by);
  string_view left = line.substr(0, pos);

  if (pos < line.size() && pos + 1 < line.size()) {
    return {left, line.substr(pos + 1)};
  } else {
    return {left, string_view()};
  }
}

Ini::Section& Ini::Document::AddSection(string name) {
  sections.insert(make_pair(name, Section()));
  return sections.at(name);
}

const Ini::Section& Ini::Document::GetSection(const string& name) const {
  return sections.at(name);
}

size_t Ini::Document::SectionCount() const {
  return sections.size();
}

Ini::Document Ini::Load(istream& input) {
  Document doc;

  for (string section; input >> section; ) {
    string_view section_view = section;
    section_view.remove_prefix(1);
    section_view.remove_suffix(1);

    Section* storage = &doc.AddSection(string(section_view));

    for (char c; input >> c;) {
      input.putback(c);

      if (c == '[') {
        break;
      }

      string key_value;
      input >> key_value;

      string_view kv_view = key_value;
      auto [key, value] = Split(kv_view, '=');
      storage->insert(make_pair(key, value));
    }
  }

  return doc;
}