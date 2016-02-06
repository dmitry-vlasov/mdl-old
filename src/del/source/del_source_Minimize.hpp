/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Minimize.hpp                                  */
/* Description:     question                                                 */
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

class Minimize :
	public del :: Minimize,
	public Scalar<Minimize> {
public :
	Minimize
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory
	);
	Minimize (const del :: Theory*);
	virtual ~ Minimize();

	// Minimize interface
	virtual const del :: Theory* getMinimalTheory() const;
	virtual const del :: Minimization* minimize() const;

	// Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

private :
	void startTheory() const;
	void minimizeTheory() const;;
	void finishTheory() const;
	const del :: Minimization* createMinimization() const;

	const Location location_;
	const del :: Comments* comments_;
	const value :: Theory theoryName_;
	const del :: Theory* theory_;
	mutable del :: Theory* minimalTheory_;
};

}
}


