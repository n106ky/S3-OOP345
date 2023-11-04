#include <iostream>
#include <fstream>
#include <string>
#include "Filesystem.h"

using namespace std;

namespace sdds {
   Filesystem::Filesystem() {}
   // Custom constructor
   string Filesystem::TrimSource(std::string& src) {

      // TRIM OUT DESCRIPTION:
      string dir = src;
      string content{};
      string file{};

      size_t stroke = src.find('|');

      dir = dir.substr(0, stroke);

      // TRIM OUT SPACES:
      size_t fSpacePos = dir.find_first_not_of(' ');
      size_t lSpacePos = dir.find_last_not_of(' ');
      dir = dir.substr(fSpacePos, (lSpacePos - fSpacePos + 1));

      if (stroke != std::string::npos) {
         content = src;
         content = content.substr(stroke + 1, src.length() - 1);
         fSpacePos = content.find_first_not_of(' ');
         lSpacePos = content.find_last_not_of(' ');
         content = content.substr(fSpacePos, (lSpacePos - fSpacePos + 1));
      }

      // TRIM OUT AFTER 1ST SLASH:
      size_t slash = dir.find('/');
      if (slash != std::string::npos) {
         size_t fSlashPos = dir.find_first_of('/');
         dir = dir.substr(0, fSlashPos + 1);
      }
      src = dir;

      //cout << "src:      |" << src << '|' << endl;
      //cout << "dir:      |" << dir << '|' << endl;
       //cout << "content: |" << content << '|' << endl;
      return content;
   }

   void Filesystem::assortDir(const std::string root, const std::string content) {

      size_t slash = root.find('/');
      if (slash != std::string::npos) {
         if (!m_current->find(root)) {
            // cout << "root: " << root << endl;
            *m_current += new Directory(root);
            // cout << "DIR" << endl;
         }
      }
      else {
         *m_current += new File(root, content);
         // cout << "root: " << root << endl;
         cout << "content: " << content << endl;
         // cout << "FILE" << endl;
      }
   }

   Filesystem::Filesystem(const std::string& filename, const std::string& rootdirname) {
      m_root = new Directory(rootdirname);
      m_current = m_root;
      ifstream inFile(filename);
      if (!inFile.is_open()) {
         throw("..."); // inside () can be anything
      }
      else {
         string lines{};
         while (getline(inFile, lines)) {
            string content = TrimSource(lines);
            assortDir(lines, content);
         }
      }
   }

   // Move operations (copy operations are deleted)
   Filesystem::Filesystem(Filesystem&& src) noexcept {
      *this = move(src);
   }
   Filesystem& Filesystem::operator=(Filesystem&& src) noexcept {
      if (this != &src) {
         delete m_root;
         delete m_current;
         m_root = src.m_root;
         m_current = src.m_current;

         src.m_root = nullptr;
         src.m_current = nullptr;
      }
      return *this;
   }
   // Destructor
   Filesystem::~Filesystem() {
      delete m_root;
      //delete m_current;
   }

   // Adding a resource to the current directory
   Filesystem& Filesystem::operator+=(Resource* resource) {

      return *this;
   }

   // Changing the current directory
   Directory* Filesystem::change_directory(const std::string& dirname) {
      Directory* dir{};

      return dir;
   }

   // Getting the current directory
   Directory* Filesystem::get_current_directory() const {
      return m_current;
   }

}