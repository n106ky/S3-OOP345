#pragma once
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H

#include "Directory.h"
#include "File.h"

namespace sdds {

   class Filesystem {
      Directory* m_root{};
      Directory* m_current{};

      std::string TrimSource(std::string&);
      void assortDir(const std::string, const std::string);

   public:
      Filesystem();
      // Custom constructor
      Filesystem(const std::string& filename, const std::string& rootname = "");

      // Move operations (copy operations are deleted)
      Filesystem(Filesystem&& other) noexcept;

      Filesystem& operator=(Filesystem&& other) noexcept;

      // Adding a resource to the current directory
      Filesystem& operator+=(Resource* resource);

      // Changing the current directory
      Directory* change_directory(const std::string& dirname = "");

      // Getting the current directory
      Directory* get_current_directory() const;

      // Destructor
      ~Filesystem();
   };

}

#endif