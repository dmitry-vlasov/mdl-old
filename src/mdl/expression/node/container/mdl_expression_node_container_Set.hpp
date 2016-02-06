/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Set.hpp                    */
/* Description:     set container for values                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/types/mdl_types.hpp"

namespace mdl {
namespace expression {
namespace node {
namespace container {

template<class V, template<class> class H, class A>
class Set : public Scalar<Set<V, H, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;
	typedef
		typename set :: Set<Value_, H, Allocator_>
		Set_;
	typedef
		Set_ Container_;

	Set();
	Set (Value_);
	~ Set();

	void addValue (Value_);
	Value_ getValue() const;

	Container_& container();
	const Container_& getContainer() const;

	void copy (const Set&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Set_ set_;
};

	template<class V, template<class> class H, class A>
	String&
	operator << (String&, const Set<V, H, A>&);
}
}
}
}


