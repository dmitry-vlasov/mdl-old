/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Container.hpp                                   */
/* Description:     global container                                         */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace math {

template<class T, class R = value :: Integer>
class Container : public object :: Object {
private :
	enum {
		INITIAL_FORM_VECTOR_CAPACITY = size :: KILOBYTE
	};
public :
	typedef T Form_;
	typedef R Index_;

	Container (const Index_ = INITIAL_FORM_VECTOR_CAPACITY);
	virtual ~ Container();
	
	Size_t getContentVolume() const;
	Index_ getSize() const;
	Form_* getForm (Index_);
	Index_ addForm (Form_*);
	
	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

protected :
	typedef
		vector :: Vector
		<
			Form_*,
			storage :: ByValue,
			allocator :: Heap
		>
		FormVector_;

	FormVector_ formVector_;
};

}
}


