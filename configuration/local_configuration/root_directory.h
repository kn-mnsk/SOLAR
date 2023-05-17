// root_directory.h.in
#ifndef ROOT_DIRECTORY_H
#define ROOT_DIRECTORY_H

//extern char * project_root = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/";
//extern std::string localdata_root = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/.local_data/";
//extern std::string commondata_root = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/../../../.common_data/";
//extern std::string shader_root = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/shader/";

//inline std::string pathCommonResources(const std::string file){
//    std::string commonResources = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/../.commonResources/";
//    return (commonResources + file);
//}
inline std::string pathToResources(const std::string file){
    std::string commonResources = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/resources/";
return (commonResources + file);
}
inline std::string pathToShader(const std::string file){
    std::string shader = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/shader/";
    return (shader + file);
}
//
//inline std::string get_OGLDEVshader(const std::string file){
//    std::string shader = "C:/Users/mnskk/Development/MyDvlpWindows/OpenGLWindow/SOLAR/../../../.commonSDK/.Tutorial/OGLDEV/Shaders/";
//return (shader + file);
//}
// ROOT_DIRECTORY_H
#endif
