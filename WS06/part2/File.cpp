#include <iostream>
#include "Flags.h"
#include "File.h"

using namespace std;

namespace sdds {

   File::File(const std::string& name, const std::string& contents): m_name(name), m_contents(contents) {}

   void File::update_parent_path(const std::string& parentPath) {
      m_parentPath = parentPath;
   }
   sdds::NodeType File::type() const {
      return NodeType::FILE;
   }
   std::string File::path() const {
      return m_parentPath + m_name;
   }
   std::string File::name() const {
      return m_name;
   }
   int File::count() const {
      return -1;
   }
   size_t File::size() const {
      return m_contents.size();
   }

}