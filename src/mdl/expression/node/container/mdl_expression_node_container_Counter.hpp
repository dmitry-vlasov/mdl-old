/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_node_container_Counter.hpp                */
/* Description:     fictive container for values: it only counts them        */
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
class Counter : public Scalar<Counter<V, H, A>, A> {
public :
	typedef V Value_;
	typedef A Allocator_;

	Counter();
	Counter (Value_);
	~ Counter();

	void addValue (Value_);
	value :: Integer getCount() const;

	void copy (const Counter&);

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	value :: Integer count_;
};

	template<class V, template<class> class H, class A>
	String&
	operator << (String&, const Counter<V, H, A>&);
}
}
}
}


