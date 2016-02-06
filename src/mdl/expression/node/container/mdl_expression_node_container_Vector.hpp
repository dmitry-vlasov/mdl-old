/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Vector.hpp                 */
/* Description:     vector container for values                              */
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
class Vector : public Scalar<Vector<V, H, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;
	typedef
		typename vector :: Vector<Value_, H, Allocator_>
		Vector_;
	typedef
		Vector_ Container_;

	Vector();
	Vector (Value_);
	~ Vector();

	void addValue (Value_);
	Value_ getValue() const;

	Container_& container();
	const Container_& getContainer() const;

	void copy (const Vector&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	Vector_ vector_;
};

	template<class V, template<class> class H, class A>
	String&
	operator << (String&, const Vector<V, H, A>&);
}
}
}
}


