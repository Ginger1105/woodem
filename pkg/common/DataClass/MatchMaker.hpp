// 2010 © Václav Šmilauer <eudoxos@arcig.cz>

#include<yade/lib-serialization/Serializable.hpp>
#include<string>

namespace py = boost::python;

/* Future optimizations, in postLoad:

1. Use matches to update lookup table/hash for faster matching, instead of traversing matches every time
2. Use fallback to update fallbackPtr, instead of string-comparison of fallback every time

*/
class MatchMaker: public Serializable {
	#if 0
		Real fallbackAvg(Real v1, Real v2) const{ return (v1+v2)/2.; }
		Real fallbackMin(Real v1, Real v2) const{ return min(v1,v2); }
		Real fallbackMax(Real v1, Real v2) const{ return max(v1,v2); }
		Real fallbackHarmAvg(Real v1, Real v2) const { return 2*v1*v2/(v1+v2); }
		Real fallbackVal(Real v1, Real v2) const { return val; }
		Real (MatchMaker::*)(Real,Real) fallbackPtr;
	#endif
	public:
		virtual ~MatchMaker();
		Real computeFallback(Real val1, Real val2) const ;
		void postLoad(MatchMaker&);
		// return value looking up matches for id1+id2 (the order is arbitrary)
		// if no match is found, use val1,val2 and fallback strategy to compute new value.
		// if no match is found and val1 or val2 are not given, throw exception
		Real operator()(const int id1, const int id2, const Real val1=NaN, const Real val2=NaN) const;
		YADE_CLASS_BASE_DOC_ATTRS_CTOR_PY(MatchMaker,Serializable,"Class matching pair of ids to return pre-defined or derived value of a scalar parameter.",
			((std::vector<Vector3r>,matches,,,"Array of ``(id1,id2,value)`` items; queries matching ``id1``+``id2`` or ``id2``+``id1`` will return ``value``"))
			((std::string,fallback,"avg",Attr::triggerPostLoad,"Alogorithm used to compute value when no match for ids is found. Possible values are\n* 'avg' (arithmetic average)\n* 'min' (minimum value)\n* 'max' (maximum value)\n* 'harmAvg' (harmonic average)\n* 'val' (return value specified by :yref:`val<MatchMaker.val>`\n"))
			((Real,val,NaN,,"Constant value returned if there is no match and :yref:`fallback<MatchMaker::fallback>` is ``val``"))
			, /*ctor*/
			, /*py*/ .def("__call__",&MatchMaker::operator(),(py::arg("id1"),py::arg("id2"),py::arg("val1")=NaN,py::arg("val2")=NaN),"Ask the instance for scalar value for given pair *id1*,*id2* (the order is irrelevant). Optionally, *val1*, *val2* can be given so that if there is no :yref:`match<MatchMaker.matches>`, return value can be computed using given :yref:`fallback<MatchMaker.fallback>`. If there is no match and *val1*, *val2* are not given, an exception is raised.")
			.def("computeFallback",&MatchMaker::computeFallback,(py::arg("val1"),py::arg("val2")),"Compute fallback value for *val1* and *val2*, using algorithm specified by :yref:`fallback<MatchMaker.fallback>`.")
		);
};
REGISTER_SERIALIZABLE(MatchMaker);