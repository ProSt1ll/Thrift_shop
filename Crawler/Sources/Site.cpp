#include "../Headers/Site.h"

using siteSearch::Chapters;
using siteSearch::Parameters;

// TemplateParameter

// конструкторы

siteSearch::TemplateParameter::TemplateParameter() {
    tag = "";
    id = "";
    cssClass = "";
}

siteSearch::TemplateParameter::TemplateParameter(const std::string &tag_, const std::string &id_,
                                                 const std::string &cssClass_) {
    tag = tag_;
    id = id_;
    cssClass = cssClass_;

}

// Get методы

std::string siteSearch::TemplateParameter::getTag() const {
    return tag;
}

std::string siteSearch::TemplateParameter::getId() const {
    return id;
}

std::string siteSearch::TemplateParameter::getCssClass() const {
    return cssClass;
}

nlohmann::json siteSearch::TemplateParameter::getJson() const {
    nlohmann::json resultJson;

    resultJson["tag"] = tag;
    resultJson["id"] = id;
    resultJson["cssClass"] = cssClass;

    return resultJson;
}

// Set методы

void siteSearch::TemplateParameter::setTag(const std::string &newTag) {
    tag = newTag;
}

void siteSearch::TemplateParameter::setId(const std::string &newId) {
    id = newId;
}

void siteSearch::TemplateParameter::setCssClass(const std::string &newCssClass) {
    cssClass = newCssClass;
}

// перегрузка операторов

bool siteSearch::TemplateParameter::operator==(const TemplateParameter &comparableTemplateParameter) const {
    return (id == comparableTemplateParameter.id && tag == comparableTemplateParameter.tag &&
            cssClass == comparableTemplateParameter.cssClass);
}

// Site

// конструкторы

siteSearch::Site::Site() = default;

siteSearch::Site::Site(const json &settings) {

}

// Get методы

std::string siteSearch::Site::getChapterUrl(const siteSearch::Chapters &chapter) const {
    return chapterMap.at(chapter);
}

siteSearch::TemplateParameter siteSearch::Site::getTemplateParameter(const siteSearch::Parameters &parameter) const {
    return parameterMap.at(parameter);
}

std::set<Chapters> siteSearch::Site::getChapters() const {
    std::set<Chapters> returnSet;
    for (const auto &element: chapterMap) {
        returnSet.emplace(element.first);
    }
    return returnSet;
}

std::set<Parameters> siteSearch::Site::getParameters() const {
    std::set<Parameters> returnSet;
    for (const auto &element: parameterMap) {
        returnSet.emplace(element.first);
    }
    return returnSet;
}

// Set методы

void siteSearch::Site::setChapterUrl(const Chapters &chapter, const std::string &url) {
    chapterMap.insert(std::pair<Chapters, std::string>{chapter, url});
}

void siteSearch::Site::setTemplateParameter(const Parameters &parameter,
                                            const siteSearch::TemplateParameter &templateParameter) {
    parameterMap.insert(std::pair<Parameters, siteSearch::TemplateParameter>{parameter, templateParameter});
}

// перегрузка операторов

bool siteSearch::Site::operator==(const siteSearch::Site &site) {

    if (chapterMap.size() != site.chapterMap.size() || parameterMap.size() != site.parameterMap.size())
        return false;

    for (const auto &element: chapterMap) {
        if (site.chapterMap.at(element.first) != element.second)
            return false;
    }

    for (const auto &element: parameterMap) {
        if (!(site.parameterMap.at(element.first) == element.second))
            return false;
    }

    return true;
}

// delete методы

void siteSearch::Site::deleteChapter(const Chapters &chapter) {
    chapterMap.erase(chapter);
}

void siteSearch::Site::deleteParameter(const Parameters &parameter) {
    parameterMap.erase(parameter);
}

// основной функционал

bool siteSearch::Site::resetSettings(const json &settings) {
    return false;
}

json siteSearch::Site::crawl(const std::set<Parameters> &parameters_, const std::set<Chapters> &chapters_) const {
    return nlohmann::json();
}

json siteSearch::Site::getSettings() const {
    nlohmann::json resultJson;

    resultJson["chapterMap"] = chapterMap;

    resultJson["parameterMap"] = nlohmann::json({});

    for (const auto &element: parameterMap) {
        std::string key = std::to_string(element.first);
        resultJson["parameterMap"][key] = element.second.getJson();
    }

    return resultJson;
}
