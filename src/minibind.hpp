/*
 * =====================================================================================
 *
 *       Filename:  minibind.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/04/2013 11:12:23 PM
 *       Revision:  none
 *       Compiler:  g++ -std=c++11
 *
 *         Author:  Vytis Valentinavičius (), vytis.valentinavicius@gmail.com
 *        Company:  Nolife4Life
 *
 * =====================================================================================
 */

/**
 * Placeholders:
 */
template<int I>
class placeholder {};
placeholder<1> _1;
placeholder<2> _2;
placeholder<3> _3;

/**
 * Argument list wrapper
 */
template<typename R>
class param_list0 {
  public:
    param_list0() {}

    template<typename F, typename List0>
      R operator()(F f, List0 list) {
        return f();
      }

    template<typename T>
      T operator[](T v) const { return v; }
};


template<typename R, typename P1>
class param_list1 {
  public:
    param_list1(P1 p1):p1_(p1) {}

    /**
     * Calling function, which passes arguments from list to function.
     */
    template<typename F, typename List1>
      R operator()(F f, List1 list) {
        return f(list[p1_]);
      }

    /**
     * Parameter keeping operators
     */
    P1 operator[](placeholder<1>) const { return p1_; }
    template<typename T>
      T operator[](T v) const { return v; }
  private:
    P1 p1_;
};

template<typename R, typename P1, typename P2>
class param_list2 {
  public:
    param_list2(P1 p1, P2 p2):p1_(p1),p2_(p2) {}

    template<typename F, typename List2>
      R operator()(F f, List2 list) {
        return f(list[p1_], list[p2_]);
      }

    P1 operator[](placeholder<1>) const { return p1_; }
    P2 operator[](placeholder<2>) const { return p2_; }
    template<typename T>
      T operator[](T v) const { return v; }
  private:
    P1 p1_;
    P2 p2_;
};

template<typename R, typename P1, typename P2, typename P3>
class param_list3 {
  public:
    param_list3(P1 p1, P2 p2, P3 p3):p1_(p1),p2_(p2),p3_(p3) {}

    template<typename F, typename List3>
      R operator()(F f, List3 list) {
        return f(list[p1_], list[p2_], list[p3_]);
      }

    P1 operator[](placeholder<1>) const { return p1_; }
    P2 operator[](placeholder<2>) const { return p2_; }
    P3 operator[](placeholder<3>) const { return p3_; }
    template<typename T>
      T operator[](T v) const { return v; }
  private:
    P1 p1_;
    P2 p2_;
    P3 p3_;
};

/**
 * Binder class
 */
template<typename R, typename F, typename List>
class binder {
  public:
    binder(F f, List list):f_(f), list_(list) {}

    R operator()() {
      param_list0<R> list;
      return list_(f_, list);
    }

    template<typename P1>
      R operator()(P1 p1) {
        param_list1<R, P1> list(p1);
        return list_(f_, list);
      }

    template<typename P1, typename P2>
      R operator()(P1 p1, P2 p2) {
        param_list2<R, P1, P2> list(p1, p2);
        return list_(f_, list);
      }
  private:
    F f_;
    List list_;
};

/**
 * Bind function
 */
template<typename R, typename F>
binder<R, F, param_list0<R> > bind(F f) {
  typedef param_list0<R> list_type;
  list_type list;
  return binder<R, F, list_type>(f, list);
}

template<typename R, typename F, typename P1>
binder<R, F, param_list1<R, P1> > bind(F f, P1 p1) {
  typedef param_list1<R, P1> list_type;
  list_type list(p1);
  return binder<R, F, list_type>(f, list);
}

template<typename R, typename F, typename P1, typename P2>
binder<R, F, param_list2<R, P1, P2> > bind(F f, P1 p1, P2 p2) {
  typedef param_list2<R, P1, P2> list_type;
  list_type list(p1, p2);
  return binder<R, F, list_type>(f, list);
}

template<typename R, typename F, typename P1, typename P2, typename P3>
binder<R, F, param_list3<R, P1, P2, P3> > bind(F f, P1 p1, P2 p2, P3 p3) {
  typedef param_list3<R, P1, P2, P3> list_type;
  list_type list(p1, p2, p3);
  return binder<R, F, list_type>(f, list);
}
