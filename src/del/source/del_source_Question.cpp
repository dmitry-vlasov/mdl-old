/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_source_Question.cpp                                  */
/* Description:     question                                                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_SOURCE_QUESTION_CPP_
#define DEL_SOURCE_QUESTION_CPP_

#include "del/auxiliary/del_auxiliary.hpp"
#include "del/source/del_source.hpp"

namespace del {
namespace source {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Question :: Question
	(
		const del :: Theory* theory,
		const del :: Formula* formula
	) :
	location_ (),
	comments_ (NULL),
	formula_ (formula),
	name_ (theory->getName()),
	theory_ (theory),
	cloneTheory_ (true),
	usePrebuildModel_ (false),
	useStackModel_ (false) {
	}
	inline
	Question :: Question
	(
		const Location& location,
		const del :: Comments* comments,
		const value :: Theory name,
		const del :: Formula* formula
	) :
	location_ (location),
	comments_ (comments),
	formula_ (formula),
	name_ (name),
	theory_ (Math :: theories()->get (name)),
	cloneTheory_ (true),
	usePrebuildModel_ (false),
	useStackModel_ (false) {
	}
	Question :: ~ Question()
	{
		deleteAggregateObject (comments_);
		deleteAggregateObject (formula_);
	}

	void
	Question :: setCloneTheory (const bool cloneTheory) {
		cloneTheory_ = cloneTheory;
	}
	void
	Question :: setUsePrebuildModel (const bool usePrebuildModel) {
		usePrebuildModel_ = usePrebuildModel;
	}
	void
	Question :: setUseStackModel (const bool useStackModel) {
		useStackModel_ = useStackModel;
	}

	// Solvable implementation
	const del :: Answer*
	Question :: solve (del :: Model* model) const
	{
		const del :: Answer* answer = NULL;
		Timers :: solving().start();
		try {
			usePrebuildModel_ = (model != NULL);
			del :: Theory* theory = NULL;
			del :: Formula* formula = NULL;
			if (cloneTheory_) {
				theory = theory_->clone();
				formula = formula_->clone();
			} else {
				theory = const_cast<del :: Theory*>(theory_);
				formula = const_cast<del :: Formula*>(formula_);
			}
			formula->primitivize (theory);
			theory->normalize();

			//std :: cout << *formula << std :: endl;
			//std :: cout << *theory << std :: endl;

			if (!usePrebuildModel_) {
				if (useStackModel_) {
					model = new model :: Structure<allocator :: Stack>();
				} else {
					model = new model :: Structure<allocator :: Heap>();
				}
			}

			//std :: cout << *model << std :: endl;

			const bool isTrue = model->satisfies (theory, formula);

			if (isTrue && Counter :: stop (1)) {
				std :: cout << *theory << std :: endl;
				std :: cout << *model << std :: endl;
				std :: cout << "question = " << *formula << std :: endl;
				std :: cout << "image = " << *formula->getImage() << std :: endl;
			}

			Del :: volume().countModel (model);
			if (!usePrebuildModel_) {
				if (!useStackModel_) {
					model->commitSuicide();
				}
			}
			answer = new source :: Answer
				(
					location_,
					NULL,
					name_,
					isTrue,
					formula_->clone()
				);
			if (cloneTheory_) {
				theory->commitSuicide();
				formula->commitSuicide();
			}
		} catch (exception :: OutOfTime& outOfTime) {
			if (Config :: verbose()) {
				std :: cout << "failed to answer a question " << *this << " : ";
				std :: cout << "out of time." << std :: endl;
			}
		}
		Timers :: solving().stop();
		return answer;
	}

using manipulator :: space;
using manipulator :: underline;
using manipulator :: endLine;

	// object :: Writable implementation
	void
	Question :: replicate (String& string) const
	{
		if (comments_ != NULL) {
			comments_->replicate (string);
		}
		string << location_.getIndent();
		string << Token :: does_ << space;
		string << Table :: theories()->get (name_) << space;
		string << Token :: models_ << space;
		formula_->replicate (string);
		string << space << Token :: question_ << endLine;
	}
	void
	Question :: translate (String& string) const {
		replicate (string);
	}

	// object :: Object implementation
	void
	Question :: commitSuicide() {
		delete this;
	}
	Size_t
	Question :: getSizeOf() const {
		return sizeof (Question);
	}
	Size_t
	Question :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (comments_);
		volume += getAggregateVolume (formula_);
		return volume;
	}

	/****************************
	 *		Protected members
	 ****************************/
}
}

#endif /*DEL_SOURCE_QUESTION_CPP_*/
