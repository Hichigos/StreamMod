#include "modules_loader.h"


using string = std::string;

ModulesLoader::ModulesLoader() {

	m_authorizedModuleNames = {
		"win-wasapi", "win-mf", "win-capture",
		"rtmp-services",
		"obs-outputs", "obs-x264",
	};
}

ModulesLoader::~ModulesLoader() {}

void ModulesLoader::loadAuthorized() {

	for (auto &module_name : m_authorizedModuleNames) {
		loadModule(module_name + ".dll", "./");
	}
	postLoad();
}

void ModulesLoader::addPath(const string &bin, const string &data) {
	obs_add_module_path(bin.c_str(), data.c_str());
}

void ModulesLoader::loadModule(const string &bin_path, const string &data_path) {

	obs_module* module;

	int code = obs_open_module(&module, bin_path.c_str(), data_path.c_str());
	if (code != MODULE_SUCCESS) {
		blog(LOG_DEBUG, "Failed to load module file '%s': %d", bin_path.c_str(), code);
		return;
	}
	obs_init_module(module);
}

void ModulesLoader::postLoad() {
	obs_log_loaded_modules();
	obs_post_load_modules();
}