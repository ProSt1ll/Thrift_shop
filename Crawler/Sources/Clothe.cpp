#include "../Headers/Clothe.h"

using item::Clothe;

Clothe::Clothe() {
    cost = 0;
    title = "";
    url = "";
    person = undefinedPerson;
    size = undefinedSize;
    image = "";
}

Clothe::Clothe(const std::string &title_, const int cost_, const std::string &url_, const Persons person_,
               const Sizes size_, const std::string &image_) {
    cost = cost_;
    title = title_;
    url = url_;
    person = person_;
    size = size_;
    image = image_;
}

Clothe::Clothe(const Clothe &copyItem) {
    cost = copyItem.cost;
    title = copyItem.title;
    url = copyItem.url;
    person = copyItem.person;
    size = copyItem.size;
    image = copyItem.image;
}

std::size_t Clothe::getCost() const {
    return cost;
}

std::string Clothe::getTitle() const {
    return title;
}

std::string Clothe::getUrl() const {
    return url;
}

item::Persons Clothe::getPerson() const {
    return person;
}

item::Sizes Clothe::getSize() const {
    return size;
}

void Clothe::setCost(const std::size_t newCost) {
    cost = newCost;
}

void Clothe::setTitle(const std::string &newTitle) {
    title = newTitle;
}

void Clothe::setURL(const std::string &newURL) {
    url = newURL;
}

void Clothe::setPerson(const item::Persons newPerson) {
    person = newPerson;
}

void Clothe::setSize(const item::Sizes newSize) {
    size = newSize;
}

bool Clothe::isEmpty() const {
    return (cost == 0 && title.empty() && url.empty() && person == undefinedPerson && size == undefinedSize &&
            image.empty());
}

std::string Clothe::getImage() const {
    return image;
}

void Clothe::setImage(const std::string &newImage) {
    image = newImage;
}

nlohmann::json Clothe::getJson() const {
    nlohmann::json resultJson;

    resultJson["cost"] = cost;
    resultJson["title"] = title;
    resultJson["url"] = url;
    resultJson["person"] = person;
    resultJson["size"] = size;
    resultJson["image"] = image;

    return resultJson;
}

bool item::operator==(const Clothe &lhs, const Clothe &rhs) {
    return (lhs.url == rhs.url && lhs.title == rhs.title && lhs.image == rhs.image &&
            lhs.size == rhs.size && lhs.person == rhs.person && lhs.cost == rhs.cost);
}

bool item::operator!=(const Clothe &lhs, const Clothe &rhs) {
    return !item::operator==(lhs, rhs);
}

Clothe &Clothe::operator=(const Clothe &copyItem) = default;
