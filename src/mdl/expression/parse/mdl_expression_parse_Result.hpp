/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_parse_Result.hpp                          */
/* Description:     parsing result class                                     */
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
namespace parse {

class Result : public Scalar<Result, allocator :: Stack> {
public :
	typedef
		typename list :: List
		<
			const Tree*,
			storage :: ByValue,
			allocator :: Stack
		>
		List_;
	typedef
		typename List_ :: Node_
		Node_;

	Result ();
	Result (const Result&);
	Result (const Tree*, const bool final);

	void operator = (const Result&);
	bool isObtained() const;
	void join (const Result&);
	bool confirm() const;
	const List_& getList() const;

private :
	bool confirmEmpty() const;
	bool confirmSingleton() const;
	bool confirmList() const;

	List_ list_;
	bool  final_;
};

}
}
}


