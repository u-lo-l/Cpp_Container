#include "../system/system_methods.ipp"
#include "__service.ipp"

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
std::vector<int> swap_test(std::vector<T> vector) {
    std::vector<int> v;
    vector.assign(1100 * 0.04, 11);
    std::vector<int> tmp(500 * 0.04, 5), tmp2(1000 * 0.04, 10), tmp3(1500 * 0.04, 15), tmp4(3000 * 0.04, 30);
    g_start1 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    Res("STD vector", vector);
    Res("STD tmp", tmp);
    vector.swap(tmp);
    Res("STD vector after swap", vector);
    Res("STD tmp after swap", vector);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("STD tmp3", tmp3);
    vector.swap(tmp3);
    Res("STD vector after swap", vector);
    Res("STD tmp3 after swap", tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("STD vector", vector);
    Res("STD tmp2", tmp2);
    std::swap(vector, tmp2);
    Res("STD vector after swap", vector);
    Res("STD tmp2 after swap", tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("STD vector", vector);
    Res("STD tmp4", tmp4);
    std::swap(vector, tmp4);
    Res("STD vector after swap", vector);
    Res("STD tmp4 after swap", tmp4);
    g_end1 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("STD v", v);
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
std::vector<int> swap_test(_vector<T> vector) {
    std::vector<int> v;
    vector.assign(1100 * 0.04, 11);
    _vector<int> tmp(500 * 0.04, 5), tmp2(1000 * 0.04, 10), tmp3(1500 * 0.04, 15), tmp4(3000 * 0.04, 30);
    g_start2 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    long *adr1 = reinterpret_cast<long *>(&vector);
    long *adr2 = reinterpret_cast<long *>(&tmp);
    Res("FT vector", vector);
    Res("FT tmp", tmp);
    vector.swap(tmp);
    Res("FT vector after swap", vector);
    Res("FT tmp after swap", vector);
    if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
    	v.push_back(1);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("FT tmp3", tmp3);
    vector.swap(tmp3);
    Res("FT vector after swap", vector);
    Res("FT tmp3 after swap", tmp3);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("FT vector", vector);
    Res("FT tmp2", tmp2);
    std::swap(vector, tmp2);
    Res("FT vector after swap", vector);
    Res("FT tmp2 after swap", tmp2);
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("FT vector", vector);
    Res("FT tmp4", tmp4);
    std::swap(vector, tmp4);
    Res("FT vector after swap", vector);
    Res("FT tmp4 after swap", tmp4);
    g_end2 = timer();
    v.push_back(vector[2]);
    v.push_back(vector.size());
    v.push_back(vector.capacity());
    Res("FT v", v);
    return v;
}

int main() {

    exit(run_vector_unit_test<int>("swap()", swap_test, swap_test));
}