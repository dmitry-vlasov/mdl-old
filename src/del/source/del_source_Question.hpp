/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Question.hpp                                  */
/* Description:     question                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_QUESTION_HPP_
#define DEL_SOURCE_QUESTION_HPP_

#include "del/interface/del_interface.hpp"

namespace del {
namespace source {

class Question :
	public del :: Question,
	public Scalar<Question> {
public :
	Question
	(
		const del :: Theory*,
		const del :: Formula*
	);
	Question
	(
		const Location&,
		const del :: Comments* const,
		const value :: Theory,
		const del :: Formula*
	);
	virtual ~ Question();

	void setCloneTheory (const bool = true);
	void setUsePrebuildModel (const bool = true);
	void setUseStackModel (const bool = true);

	// Solvable interface
	virtual const del :: Answer* solve (del :: Model* = NULL) const;

	// Writable interface
	virtual void translate (String&) const;
	virtual void replicate (String&) const;

	// Object interface
	virtual void commitSuicide();
	virtual Size_t getSizeOf() const;
	virtual Size_t getVolume() const;

protected :
	value :: Integer getDepth() const;

	const Location location_;
	const del :: Comments* comments_;
	const del :: Formula* formula_;
	const value :: Theory name_;
	const del :: Theory* theory_;

	mutable bool cloneTheory_;
	mutable bool usePrebuildModel_;
	mutable bool useStackModel_;
};

}
}

#endif /*DEL_SOURCE_QUESTION_HPP_*/
