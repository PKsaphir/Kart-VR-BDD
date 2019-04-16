#include "connexion.h"
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion c;
   // login l;

    c.show();
  //  l.show();




    return a.exec();
}
