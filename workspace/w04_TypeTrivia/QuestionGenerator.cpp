#include "QuestionGenerator.h"
#include "Question.h"

#include <vector>
#include <boost/type_index.hpp>

template<typename T>
struct Tpl {};

#define MAKE_F_WITH_PARAM_TYPE(type, name) \
template<typename T> \
boost::typeindex::type_index t_index_of_##name(type t) { \
    return boost::typeindex::type_id_with_cvr<T>(); \
} \
template<typename T> \
boost::typeindex::type_index param_type_index_of_##name(type t) { \
    return boost::typeindex::type_id_with_cvr<decltype(t)>(); \
}\
std::string const template_code_of_##name = "template<typename T>\nvoid " #name "(" #type " t) {}";

#define MAKE_CALL_FOR(called_function, declaration_code, calling_code) \
std::string const call_of_code_of_##called_function = #declaration_code ";\n" #calling_code ";";\
auto t_type_lambda = [](){declaration_code; return t_index_of_##calling_code.pretty_name(); }; \
auto param_type_lambda = [](){declaration_code; return param_type_index_of_##calling_code.pretty_name(); }; \
Question const q{call_of_code_of_##called_function, template_code_of_##called_function, t_type_lambda(), param_type_lambda()};

#define ADD_QUESTION_WITH_DECL(container, name, declaration, call) {\
	MAKE_CALL_FOR(name, declaration, call)\
	container.push_back(q);\
} while(false)

#define ADD_QUESTION(container, name, call) ADD_QUESTION_WITH_DECL(container, name, , call)

MAKE_F_WITH_PARAM_TYPE(T&&, f_fwd_ref)
MAKE_F_WITH_PARAM_TYPE(T&, f_lvalue_ref)
MAKE_F_WITH_PARAM_TYPE(T const &, f_lvalue_const_ref)
MAKE_F_WITH_PARAM_TYPE(T, f_value_type)
MAKE_F_WITH_PARAM_TYPE(T*, f_pointer_to_type)
MAKE_F_WITH_PARAM_TYPE(T const *, f_pointer_to_const_type)

MAKE_F_WITH_PARAM_TYPE(Tpl<T>&&, f_fwd_ref_tpl)
MAKE_F_WITH_PARAM_TYPE(Tpl<T>&, f_lvalue_ref_tpl)
MAKE_F_WITH_PARAM_TYPE(Tpl<T> const &, f_lvalue_const_ref_tpl)
MAKE_F_WITH_PARAM_TYPE(Tpl<T>, f_value_type_tpl)
MAKE_F_WITH_PARAM_TYPE(Tpl<T> *, f_pointer_to_tpl)
MAKE_F_WITH_PARAM_TYPE(Tpl<T> const *, f_pointer_to_const_tpl)



std::vector<Question> createQuestions() {
	std::vector<Question> questions{};
	ADD_QUESTION_WITH_DECL(questions, f_fwd_ref, int x{}, f_fwd_ref(x));
	ADD_QUESTION_WITH_DECL(questions, f_fwd_ref, int x{}, f_fwd_ref(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_fwd_ref, int const x{}, f_fwd_ref(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_fwd_ref, int * x = new int{5}, f_fwd_ref(x));
	ADD_QUESTION_WITH_DECL(questions, f_fwd_ref, int const * x = new int{5}, f_fwd_ref(x));
	ADD_QUESTION(questions, f_fwd_ref, f_fwd_ref(5));
	ADD_QUESTION(questions, f_fwd_ref, f_fwd_ref("string-literal aka char const[34]"));

	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref, int x{}, f_lvalue_ref(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref, int const x{}, f_lvalue_ref(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref, int * x = new int{5}, f_lvalue_ref(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref, int const * x = new int{5}, f_lvalue_ref(x));
	ADD_QUESTION(questions, f_lvalue_ref, f_lvalue_ref("string-literal aka char const[34]"));

	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref, int x{}, f_lvalue_const_ref(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref, int x{}, f_lvalue_const_ref(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref, int const x{}, f_lvalue_const_ref(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref, int * x = new int{5}, f_lvalue_const_ref(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref, int const * x = new int{5}, f_lvalue_const_ref(x));
	ADD_QUESTION(questions, f_lvalue_const_ref, f_lvalue_const_ref(5));
	ADD_QUESTION(questions, f_lvalue_const_ref, f_lvalue_const_ref("string-literal aka char const[34]"));

	ADD_QUESTION_WITH_DECL(questions, f_value_type, int x{}, f_value_type(x));
	ADD_QUESTION_WITH_DECL(questions, f_value_type, int x{}, f_value_type(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_value_type, int const x{}, f_value_type(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_value_type, int * x = new int{5}, f_value_type(x));
	ADD_QUESTION_WITH_DECL(questions, f_value_type, int const * x = new int{5}, f_value_type(x));
	ADD_QUESTION(questions, f_value_type, f_value_type(5));
	ADD_QUESTION(questions, f_value_type, f_value_type("string-literal aka char const[34]"));

	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_type, int * x = new int{5}, f_pointer_to_type(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_type, int const * x = new int{5}, f_pointer_to_type(x));
	ADD_QUESTION(questions, f_pointer_to_type, f_pointer_to_type("string-literal aka char const[34]"));

	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_const_type, int * x = new int{5}, f_pointer_to_const_type(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_const_type, int const * x = new int{5}, f_pointer_to_const_type(x));
	ADD_QUESTION(questions, f_pointer_to_const_type, f_pointer_to_const_type("string-literal aka char const[34]"));

	ADD_QUESTION_WITH_DECL(questions, f_fwd_ref_tpl, Tpl<int> x{}, f_fwd_ref_tpl(std::move(x)));
	ADD_QUESTION(questions, f_fwd_ref_tpl, f_fwd_ref_tpl(Tpl<int>{}));
	ADD_QUESTION(questions, f_fwd_ref_tpl, f_fwd_ref_tpl(Tpl<int const>{}));
	ADD_QUESTION(questions, f_fwd_ref_tpl, f_fwd_ref_tpl(Tpl<int *>{}));
	ADD_QUESTION(questions, f_fwd_ref_tpl, f_fwd_ref_tpl(Tpl<int const *>{}));

	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref_tpl, Tpl<int> x{}, f_lvalue_ref_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref_tpl, Tpl<int const> x{}, f_lvalue_ref_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref_tpl, Tpl<int *> x{}, f_lvalue_ref_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_ref_tpl, Tpl<int const *> x{}, f_lvalue_ref_tpl(x));

	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref_tpl, Tpl<int> x{}, f_lvalue_const_ref_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref_tpl, Tpl<int> const x{}, f_lvalue_const_ref_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref_tpl, Tpl<int> x{}, f_lvalue_const_ref_tpl(std::move(x)));
	ADD_QUESTION_WITH_DECL(questions, f_lvalue_const_ref_tpl, Tpl<int> const x{}, f_lvalue_const_ref_tpl(std::move(x)));


	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_tpl, Tpl<int> * x = new Tpl<int>{}, f_pointer_to_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_tpl, Tpl<int> * const x = new Tpl<int>{}, f_pointer_to_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_tpl, Tpl<int const> * const x = new Tpl<int const>{}, f_pointer_to_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_tpl, Tpl<int> * const & x = new Tpl<int>{}, f_pointer_to_tpl(x));

	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_const_tpl, Tpl<int> const * x = new Tpl<int>{}, f_pointer_to_const_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_const_tpl, Tpl<int const> const * const x = new Tpl<int const>{}, f_pointer_to_const_tpl(x));
	ADD_QUESTION_WITH_DECL(questions, f_pointer_to_const_tpl, Tpl<int> const * const & x = new Tpl<int>{}, f_pointer_to_const_tpl(x));

	return questions;
}
