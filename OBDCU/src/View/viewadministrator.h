#ifndef VIEWADMINISTRATOR_H
#define VIEWADMINISTRATOR_H

class ViewAdministrator
{
public:
    virtual ~ViewAdministrator();
    static ViewAdministrator* getInstance();

    int startView(int argc, char** argv);
private:
    static ViewAdministrator* instance_;
    ViewAdministrator();
};

#endif // VIEWADMINISTRATOR_H
