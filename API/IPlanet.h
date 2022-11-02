#pragma once

#include "IDLLoader.h"
#include <functional>
#include <iostream>
#include <memory>

/*
** This is the base class for all planets (libraries)
*/
class IPlanet
{
	
public:
	virtual ~IPlanet() = default;

	/*
	** Pure method which will be overrided.
	*/
	virtual void greet() const = 0;

};


class Planet
{
public:

    using base_t = IPlanet;

    template <typename T>
    Planet(std::shared_ptr<T> x, std::shared_ptr<dlloader::IDLLoader<Planet>> dloader) noexcept
    : _dloader{std::move(dloader)}, _self{std::move(x)}
    {
    }

    void greet() const
    {
        _self->greet();
    }


private:


    template <typename T>
    struct model final : base_t
    {
        model(T x) : _data{std::move(x)}
        {
        }

        void greet() const override
        {
            _data->greet();
        }

        T _data;
    };

    std::shared_ptr<const dlloader::IDLLoader<Planet>> _dloader;
    std::shared_ptr<const base_t> _self;
};
