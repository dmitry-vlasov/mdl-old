/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_PredicateMap.hpp                */
/* Description:     interpretation of predicates in a model of a theory      */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_MODEL_INTERPRETATION_PREDICATE_MAP_HPP_
#define DEL_MODEL_INTERPRETATION_PREDICATE_MAP_HPP_

#include "del/interface/del_interface.hpp"
#include "del/model/del_model.dpp"

namespace del {
namespace model {
namespace interpretation {

template<class A>
class PredicateMap :
	public model :: PredicateMap,
	public Scalar<PredicateMap<A>, A> {
public :
	typedef A Allocator_;
	typedef typename node :: positive :: Singleton<Allocator_> Singleton_;
	typedef Predicate<Allocator_> Predicate_;

	PredicateMap (del :: Model*);
	PredicateMap (del :: Model*, const value :: Integer);
	template<class A1>
	PredicateMap (const PredicateMap<A1>&, del :: Model*);
	virtual ~ PredicateMap();

	template<class A1>
	void copy (const PredicateMap<A1>&, del :: Model*);

	// del :: model :: PredicateMap interface
	virtual value :: Integer getSize() const;
	virtual model :: Predicate* getPredicate (const value :: Integer) const;
	virtual model :: Predicate* getPredicate (const Symbol);
	virtual const model :: Predicate* getPredicate (const Symbol) const;
	virtual void registerVariable (const Symbol);
	virtual void copy (const model :: PredicateMap&, del :: Model*);
	virtual bool isEqual (const model :: PredicateMap&, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class PredicateMap;

	typedef
		map :: Scalar
		<
			Symbol,
			Predicate_*,
			Allocator_
		>
		Map_;

	void createPredicate (const Symbol) const;

	Model* model_;
	mutable Map_ map_;
	Predicate_* top_;
	enum {
		INITIAL_MAP_CAPACITY = 256,
		INITIAL_CLOSURE_CAPACITY = 32
	};
};

}
}
}

#endif /*DEL_MODEL_INTERPRETATION_PREDICATE_MAP_HPP_*/
