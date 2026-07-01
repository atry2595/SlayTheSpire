#ifndef RNG_H
#define RNG_H

#include <QRandomGenerator>
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <vector>

class RNG
{
private:
    uint32_t seed;
    QRandomGenerator engine;

public:

    RNG()
        : RNG(static_cast<uint32_t>(
              std::chrono::high_resolution_clock::now()
                  .time_since_epoch()
                  .count()))
    {}

    RNG(uint32_t seed)
        : seed(seed),
        engine(seed)
    {}

    uint32_t get_seed() const
    {
        return seed;
    }

    int randint(int min, int max)
    {
        return engine.bounded(min, max + 1);
    }

    double random()
    {
        return engine.generateDouble();
    }

    double random(double min, double max)
    {
        return min + random() * (max - min);
    }

    bool chance(double number)
    {
        return random() <= number;
    }

    template<typename T>
    void shuffle(std::vector<T>& vec)
    {
        if (vec.size() <= 1)
            return;

        for (int i = static_cast<int>(vec.size()) - 1; i > 0; --i)
        {
            int j = randint(0, i);
            std::swap(vec[i], vec[j]);
        }
    }

    template<typename T>
    T& choice(std::vector<T>& vec)
    {
        if (vec.empty())
            throw std::runtime_error("RNG::choice() : empty vector.");

        return vec[randint(0, static_cast<int>(vec.size()) - 1)];
    }

    template<typename T>
    std::vector<T> sample(const std::vector<T>& vec, int count)
    {
        if (count < 0)
            count = 0;

        if (count > static_cast<int>(vec.size()))
            count = static_cast<int>(vec.size());

        std::vector<T> temp = vec;

        shuffle(temp);

        return std::vector<T>(
            temp.begin(),
            temp.begin() + count
            );
    }

    template<typename T>
    T& weighted_choice(
        std::vector<T>& vec,
        const std::vector<double>& weights)
    {
        if (vec.empty())
            throw std::runtime_error("RNG::weighted_choice() : empty vector.");

        if (vec.size() != weights.size())
            throw std::runtime_error("RNG::weighted_choice() : size mismatch.");

        double total = std::accumulate(
            weights.begin(),
            weights.end(),
            0.0);

        double r = random(0.0, total);

        double current = 0.0;

        for (size_t i = 0; i < vec.size(); ++i)
        {
            current += weights[i];

            if (r <= current)
                return vec[i];
        }

        return vec.back();
    }

    template<typename T>
    std::vector<T> weighted_sample(
        const std::vector<T>& vec,
        const std::vector<double>& weights,
        int count)
    {
        if (vec.size() != weights.size())
            throw std::runtime_error("RNG::weighted_sample() : size mismatch.");

        std::vector<T> objects = vec;
        std::vector<double> w = weights;

        if (count > static_cast<int>(objects.size()))
            count = static_cast<int>(objects.size());

        std::vector<T> result;

        for (int k = 0; k < count; ++k)
        {
            double total = std::accumulate(
                w.begin(),
                w.end(),
                0.0);

            double r = random(0.0, total);

            double current = 0.0;

            size_t index = 0;

            for (; index < w.size(); ++index)
            {
                current += w[index];

                if (r <= current)
                    break;
            }

            result.push_back(objects[index]);

            objects.erase(objects.begin() + index);
            w.erase(w.begin() + index);
        }

        return result;
    }
};

#endif // RNG_H
