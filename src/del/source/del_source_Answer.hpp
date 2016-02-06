/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Answer.hpp                                    */
/* Description:     solution                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Answer :
	public del :: Answer,
	public Scalar<Answer> {
public :
	Answer
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory,
		const bool,
		const del :: Formula* formula_
	);
	virtual ~ Answer();

	// del :: Answer interface
	virtual bool isPositive() const;

	// object :: Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const del :: Comments* comments_;
	const del :: Formula* formula_;
	const value :: Theory name_;
	const bool isPositive_;
	const del :: Theory* theory_;
};

}
}


