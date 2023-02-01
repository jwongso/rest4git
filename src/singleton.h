/// \brief Global common singleton template for rest4git.
/// \author Juniarto Saputra (jsaputra@riseup.net)
/// \version 1.0
/// \date Dec 2022
///
/// Currently there is no detailed description available.
/// \todo Add more detailed description!

namespace rest4git
{

class Notcopyable
{
public:
    explicit Notcopyable() {}
    Notcopyable(const Notcopyable&) = delete;
    Notcopyable& operator=(const Notcopyable&) = delete;
};

template <typename T>
class Singleton : public Notcopyable
{
public:
    static T& get_instance()
    {
       static T instance;
       return instance;
    }
protected:
    explicit Singleton() {}
};

}