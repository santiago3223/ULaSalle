#ifndef SINGLETON
#define SINGLETON
#include <string>

class Singleton
{
  public:
    static Singleton *instance()
    {
      if (!inst)
          inst = new Singleton();
      return inst;
    }
    Singleton(){
        inst = 0;
    }

    static void setRuta(string t)
    {
      ruta = t;
    }

    static string getRuta(){
        return ruta;
    }

  private:
    static string ruta;
    static Singleton *inst;
};


#endif // SINGLETON

