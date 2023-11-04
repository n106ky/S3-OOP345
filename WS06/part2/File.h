#pragma once
#ifndef SDDS_FILE_H
#define SDDS_FILE_H

#include "Flags.h"
#include "Resource.h"

namespace sdds {

   class File: public Resource {
      std::string m_name{};
      std::string m_parentPath{'/'};
      std::string m_contents{};
   public:
      File(const std::string&, const std::string& ="");
      void update_parent_path(const std::string&); // : sets the parent path to the parameter.
      sdds::NodeType type() const;//  a query that returns Flags::FILE.
      std::string path() const;// a query that returns the full absolute path of the file(concatenates the absolute path location and the file name).
      std::string name() const;//  a query that returns the name of the file.
      int count() const;// a query that returns - 1.
      size_t size() const;// a query that returns the size of the file in bytes.For simplicity, this is the number of characters in m_contents attribute.

   };

}

#endif