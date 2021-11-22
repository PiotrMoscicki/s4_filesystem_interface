#pragma once

#include <core/str/string_id.hpp>
#include <core/util/res.hpp>
#include <rtti/buffer.hpp>

namespace fs {
    using namespace core::str;
    using namespace core::util;

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class Path {
    public:
        inline static char NAME_SEPARATOR = '/';
        inline static char EXT_SEPARATOR = '.';

        Path() = default;
        Path(StringId path) : m_path(path) { extract_name_and_ext(); }
        bool operator==(const fs::Path& other) const { return m_path == other.m_path; }
        bool operator<(const fs::Path& other) const { return m_path < other.m_path; }

        StringId path() const { return m_path; } 
        StringId name() const { return m_name; }
        StringId ext() const { return m_ext; }

    private:
        void extract_name_and_ext() {
            std::istringstream stream(m_path.get());
            std::string last_path_elem;
            while (getline(stream, last_path_elem, NAME_SEPARATOR)) {}
            stream = std::istringstream(last_path_elem);
            std::string name;
            std::string extension;
            getline(stream, name, EXT_SEPARATOR);
            getline(stream, extension);
            m_name = StringId(name);
            m_ext = StringId(extension);
        }

        StringId m_path;
        StringId m_name;
        StringId m_ext;

    }; // class Path

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class IFilesystem {
    public:
        enum class ErrParent {
            UNDEFINED
        };

        enum class ErrChildrenCount {
            UNDEFINED
        };
        
        enum class ErrChild {
            UNDEFINED
        };
        
        enum class ErrAdd {
            UNDEFINED
        };
        
        enum class ErrRemove {
            UNDEFINED
        };
        
        enum class ErrRename {
            UNDEFINED
        };
        
        enum class ErrMove {
            UNDEFINED
        };
        
        enum class ErrRead {
            UNDEFINED
        };
        
        enum class ErrWrite {
            UNDEFINED
        };
        
        virtual Path root() const = 0;
        virtual Res<Path, ErrParent> parent(const Path& path) const = 0;
        virtual Res<size_t, ErrChildrenCount> children_count(const Path& path) const = 0;
        virtual Res<Path, ErrChild> child(const Path& path, size_t idx) const = 0;

        virtual bool is_dir(const Path& path) const = 0;
        virtual bool is_file(const Path& path) const = 0;

        virtual Res<Path, ErrAdd> add(const Path& parent, const std::string& relative_path) = 0;
        virtual Res<void, ErrRemove> remove(const Path& path) = 0;
        virtual Res<Path, ErrRename> rename(const Path& path, const std::string& new_name) = 0;
        virtual Res<Path, ErrMove> move(const Path& path, const Path& new_parent) = 0;

        virtual Res<rtti::Buffer, ErrRead> read(const Path& path) const = 0;
        virtual Res<void, ErrWrite> write(const Path& path, const rtti::Buffer& buf) const = 0;

    }; // class IFilesystem

} // namespace fs