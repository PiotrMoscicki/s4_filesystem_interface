#pragma once

#include <string>
#include <sstream>

#include <rtti/rtti.hpp>

namespace fs {

    enum class ErrParent {
        INVALID_PATH
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

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class Path {
    public:
        inline static char NAME_SEPARATOR = '/';
        inline static char EXT_SEPARATOR = '.';

        Path() = default;
        Path(std::string path) : m_path(std::move(path)) { extract_name_and_ext(); }

        const std::string& path() const { return m_path; } 
        const std::string& name() const { return m_name; }
        const std::string& ext() const { return m_ext; }

    private:
        void extract_name_and_ext() {
            std::istringstream stream(m_path);
            std::string last_path_elem;
            while (getline(stream, last_path_elem, NAME_SEPARATOR)) {}
            stream = std::istringstream(last_path_elem);
            getline(stream, m_name, EXT_SEPARATOR);
            getline(stream, m_ext);
        }

        std::string m_path;
        std::string m_name;
        std::string m_ext;

    }; // class Path

    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    class IFilesystem {
    public:
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