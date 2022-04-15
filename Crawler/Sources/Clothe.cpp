#include "../Headers/Clothe.h"

using item::Clothe;

Clothe::Clothe() {
    cost = 0;
    title = "";
    url = "";
    person = undefinedPerson;
    size = undefinedSize;
}

Clothe::Clothe(const int cost_, const std::string &title_, const std::string &url_, const Persons person_,
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

std::string item::Clothe::getImage() const {
    return image;
}

void item::Clothe::setImage(const std::string &newImage) {
    image = newImage;
}

Clothe &Clothe::operator=(const Clothe &copyItem) = default;
