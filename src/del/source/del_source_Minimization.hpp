/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Minimization.hpp                              */
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

class Minimization :
	public del :: Minimization,
	public Scalar<Minimization> {
public :
	Minimization
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory,
		const value :: Theory
	);
	Minimization
	(
		const value :: Theory,
		const value :: Theory
	);
	virtual ~ Minimization();

	// del :: Minimization interface
	virtual bool checkCorrectness() const;
	virtual void replicateCompletely (String&) const;

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
	const value :: Theory theoryName_;
	const value :: Theory minimizedTheoryName_;
	const del :: Theory* theory_;
	const del :: Theory* minimizedTheory_;
};

}
}


