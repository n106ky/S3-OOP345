#pragma once
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H
#include <vector>
#include "Flags.h"
#include "Resource.h"

namespace sdds {

   class Directory : public Resource {

      std::string m_dirname{};
      std::string m_parentPath{'/'};
      std::vector<Resource*> m_contents{};

   public:
      Directory(std::string);
      // RULE OF FIVE:
      ~Directory();
      Directory(const Directory&) = delete; // Copy constructor
      Directory& operator=(const Directory&) = delete; // Copy assignment
      Directory(Directory&&) = delete; // Move constructor
      Directory& operator=(Directory&&) = delete; // Move assignment

      void update_parent_path(const std::string&);
      sdds::NodeType type() const;
      std::string path() const;
      std::string name() const;
      int count() const;
      size_t size() const;
      Directory& operator+=(Resource*);

      Resource* find(const std::string& name, const std::vector<OpFlags>& = {});


      // New members

      // Deleting a resource from the directory
      void remove(const std::string& name, const std::vector<OpFlags>& flags = {});

      // Displaying contents of the directory
      void display(std::ostream& out, const std::vector<FormatFlags>& flags = {}) const;
   };

}

#endif