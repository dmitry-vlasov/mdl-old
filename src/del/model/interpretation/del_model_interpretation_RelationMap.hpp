/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_model_interpretation_RelationMap.hpp                 */
/* Description:     map of interpretations in a model of a theory            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"
#include "del/model/interpretation/del_model_interpretation_Relation.hpp"

namespace del {
namespace model {
namespace interpretation {

template<class A>
class RelationMap :
	public model :: RelationMap,
	public Scalar<RelationMap<A>, A> {
public :
	typedef A Allocator_;
	typedef Relation<Allocator_> Relation_;
	typedef typename node :: positive :: Pair<Allocator_> Pair_;

	RelationMap (Model*);
	RelationMap (Model*, const value :: Integer);
	template<class A1>
	RelationMap (const RelationMap<A1>&, Model*);
	virtual ~ RelationMap();

	template<class A1>
	void copy (const RelationMap<A1>&, del :: Model*);

	// del :: model :: RelationMap interface
	virtual value :: Integer getSize() const;
	virtual model :: Relation* getRelation (const value :: Integer) const;
	virtual model :: Relation* getRelation (const Symbol);
	virtual void registerRelation (const Symbol);
	virtual void copy (const model :: RelationMap&, del :: Model*);
	virtual bool isEqual (const model :: RelationMap&, const bool show = false) const;

	// del :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	template<class>
	friend class RelationMap;

	typedef
		map :: Scalar
		<
			Symbol,
			Relation_*,
			Allocator_
		>
		Map_;

	Model* model_;
	mutable Map_ map_;
	enum {
		INITIAL_MAP_CAPACITY = 256
	};
};

}
}
}


