#include <string>
#include <nlohmann/json.hpp>

#ifndef CRAWLER_ITEM_H
#define CRAWLER_ITEM_H


namespace item {

    enum Persons {
        undefinedPerson, man, woman, boy, girl
    };

    enum Sizes {
        undefinedSize, xxs, xs, s, m, l, x, xl, xxl, xxxl
    };

    class Clothe {
    private:
        // стоимость товара
        std::size_t cost;
        // название товара
        std::string title;
        // ссылка на страницу, где искать товар
        std::string url;
        // для кого предназначен товар
        Persons person;
        // размер одежды
        Sizes size;
        // ссылка на изображение
        std::string image;

    public:

        // Конструкторы

        Clothe();


        explicit Clothe(const std::string &title_, int cost_ = 0, const std::string &url_ = "",
                        Persons person_ = undefinedPerson, Sizes size_ = undefinedSize, const std::string &image_ = "");

        Clothe(Clothe const &copyItem);

        // Get методы

        std::size_t getCost() const;

        std::string getTitle() const;

        std::string getUrl() const;

        std::string getImage() const;

        Persons getPerson() const;

        Sizes getSize() const;

        // Set методы

        void setCost(std::size_t newCost);

        void setTitle(const std::string &newTitle);

        void setURL(const std::string &newURL);

        void setImage(const std::string &newImage);

        void setPerson(Persons newPerson);

        void setSize(Sizes newSize);

        // Перегрузка операторов

        Clothe &operator=(const Clothe &copyItem);

        bool operator==(const Clothe &comparableItem);

        // Остальные методы

        // возвращает True, если поля равны полям по умолчанию (в конструкторе по умолчанию)
        bool isEmpty() const;

        // возвращает json представление класса
        nlohmann::json getJson() const;

    };
}
#endif //CRAWLER_ITEM_H
