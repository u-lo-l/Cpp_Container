#include "../system/system_methods.ipp"
#include "__service.ipp"

class B {
public:
    char *l;
    int i;
    B():l(nullptr), i(1) {};
    B(const int &ex) {
        this->i = ex;
        this->l = new char('a');
    };
    virtual ~B() {
        delete this->l;
        this->l = nullptr;
    };
    friend ostream & operator<< (ostream & os , const B & b)
    {
        os << b.l << ", " << b.i;
        return (os);
    }
};

class A : public B {
public:
    A():B(){};
    A(const B* ex){
        this->l = new char(*(ex->l));
        this->i = ex->i;
        if (ex->i == -1) throw "n";
    }
    ~A() {
        delete this->l;
        this->l = nullptr;
    };
};

template<class T>
void Res( const std::string & name , const std::vector<T> & v)
{
    std::cout << "\n" << name << " RES" << std::endl;
    std::cout << "  size   : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    for (int i = 0 ; i < v.size(); i++)
        std::cout << v.at(i) << " ";
    std::cout << std::endl;
}


template <typename T>
std::vector<int> insert_test_3(std::vector<T> vector) {
    std::vector<int> v;
    std::vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    g_start1 = timer();
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    g_end1 = timer();
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("\033[1;35mstd_v\033[0m", v);

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    std::vector<A> vv;
    Res("\033[1;35mstd_vv\033[0m", vv);
    std::vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    Res("\033[1;35mstd_v1\033[0m", v1);
    try
    {
        vv.insert(vv.begin(), v1.begin(), v1.end());
        std::cout << "??" << std::endl;
    }
    catch ( const std::exception & e ) {
        std::cerr << "\033[1;33mexcep "<< e.what() << "\033[0m" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    catch ( const char * str)
    {
        std::cerr << "\033[1;32mstr "<< str << "\033[0m" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    Res("\033[1;35mstd_vv\033[0m", vv);
    Res("\033[1;35mstd_v\033[0m", v);
    std::cout << std::endl << std::endl << std::endl;
    return v;
}

template<class T>
void Res( const std::string & name , const ft::vector<T> & v)
{
    std::cout << "\n" << name << " RES" << std::endl;
    std::cout << "  size   : " << v.size() << std::endl;
    std::cout << "capacity : " << v.capacity() << std::endl;
    for (int i = 0 ; i < v.size(); i++)
        std::cout << v.at(i) << " ";
    std::cout << std::endl;
}

template <typename T>
std::vector<int> insert_test_3(_vector<T> vector) {
    std::vector<int> v;
    _vector<int> tmp;
    tmp.assign(2600 * _ratio, 1);
    vector.assign(4200 * _ratio, 1);
    g_start2 = timer();
    vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
    g_end2 = timer();
    v.push_back(vector[3]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("\033[1;35mstd_v\033[0m", v);

    std::unique_ptr<B> k2(new B(3));
    std::unique_ptr<B> k3(new B(4));
    std::unique_ptr<B> k4(new B(-1));
    _vector<A> vv;
    Res("\033[1;35mft_vv\033[0m", vv);
    _vector<B*> v1;

    v1.push_back(&(*k2));
    v1.push_back(&(*k3));
    v1.push_back(&(*k4));
    Res("\033[1;35mft_v1\033[0m", v1);
    try 
    {
        vv.insert(vv.begin(), v1.begin(), v1.end());
        std::cout << "??" << std::endl;
    }
    catch ( const std::exception & e ) {
        std::cerr << "\033[1;33mexcep "<< e.what() << "\033[0m" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    catch ( const char * str)
    {
        std::cerr << "\033[1;32mstr "<< str << "\033[0m" << std::endl;
        v.push_back(vv.size());
        v.push_back(vv.capacity());
    }
    Res("\033[1;35mft_vv\033[0m", vv);
    Res("\033[1;35mstd_v\033[0m", v);
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("insert(range)", insert_test_3, insert_test_3));

}