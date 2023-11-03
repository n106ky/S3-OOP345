#include <iostream>
#include <algorithm>
#include "Flags.h"
#include "Directory.h"
#include "File.h"

using namespace std;

namespace sdds {

   //a custom constructor that receives the name of the directory as a string and uses it to initialize the Directory object.
   //Note : assume all directory names end with a "/" .
   Directory::Directory(std::string name){
      m_dirname = name;
   }

   Directory::~Directory() {
      for (auto& resource : m_contents) {
         delete resource;
      }
   }

   // Sets the parent path to the parameter.
   // For each resource that this directory holds, this member should also set their absolute path locations to the full absolute path of this directory.
   void Directory::update_parent_path(const std::string& parentPath) {

      m_parentPath = parentPath;
      for (auto& resource : m_contents) {
         resource->update_parent_path(path());
      }
   }

   // a query that returns Flags::DIR.
   sdds::NodeType Directory::type() const {
      return sdds::NodeType::DIR;
   }


   // a query that returns the full absolute path of the directory(a concatenation of the absolute path location and the directory name).
   std::string Directory::path() const {
      return  m_parentPath + m_dirname;
   }

   // a query that returns the name of the directory.
   std::string Directory::name() const {
      return m_dirname;
   }

   //a query that returns the number of resources that this directory holds.
   int Directory::count() const {
      // Assuming you have a private vector member `m_resources` that holds the resources.
      /*return m_contents.size();*/
      return static_cast<int>(m_contents.size());
   }

   //a query that returns the size of the directory in bytes.
   // The size of the directory is the sum of the individual sizes of each resource that this directory holds.This member returns 0u if the directory is empty.
   size_t Directory::size() const {
      size_t totalSize = 0u;
      for (const auto& resource : m_contents) {
         totalSize += resource->size();
      }
      return totalSize;
   }

   /*
   adds a resource to the directory and returns a reference to the current directory.
   This member should check for existing resources in the directory with the same name:
   if a match is found, throw and exception and do nothing else;
   if no match is found, add the resource and update the absolute path location of the added resource with the directory's full absolute path.
   */
   Directory& Directory::operator+=(Resource* resource) {
      for (auto& item : m_contents) {
         if (item->name() == resource->name()) {
            throw std::runtime_error("Resource with the same name already exists");
         }
      }
      m_contents.push_back(resource);
      resource->update_parent_path(path());

      return *this;
   }


   /*
   finds and returns the address of a resource in the directory whose name matches the given string, or nullptr if a match is not found.
   This member also takes an optional vector of flags that determine how the find is performed(defaults to an empty collection).

   if the RECURSIVE flag is in the second parameter, this member will also attempt to recursively find a match in each directory that is in the m_contents vector.
   HINT : If an element in m_contents is a directory, use its find() member function to find a match.
   
   NOTE : If the current directory holds another directory named src which contains a file named sample.txt and we want to find sample.txt,
   this member will only return the sample.txt resource if the RECURSIVE flag is set, nullptr otherwise.
   */

   Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flags) {
      Resource* res{};
      for (auto& resource : m_contents) {
         if (resource->name() == name) {
            res = resource;
         }
         if (std::find(flags.begin(), flags.end(), sdds::OpFlags::RECURSIVE) != flags.end()) {
            if (resource->type() == sdds::NodeType::DIR) {
               Directory* dir = dynamic_cast<Directory*>(resource);
               if (dir != nullptr) {
                  Resource* found = dir->find(name, flags);
                  if (found != nullptr) {
                     res = found;
                  }
               }
            }
         }
      }
      return res;
   }
}


