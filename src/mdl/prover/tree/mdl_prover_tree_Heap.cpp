/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_tree_Heap.cpp                                 */
/* Description:     main prover tree class using heap memory                 */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_TREE_HEAP_CPP_
#define MDL_PROVER_TREE_HEAP_CPP_

namespace mdl {
namespace prover {
namespace tree {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Heap :: Heap (Format& format, Format& subFormat, mdl :: proof :: Question* question) :
	format_ (format),
	subFormat_ (subFormat),
	question_ (question),
	tree_ (NULL),
	data_ (NULL) {
	}
	Heap :: ~ Heap()
	{
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			deleteAggregateObject (question_);
 		}
		deleteAggregateObject (tree_);
		deleteAggregateObject (data_);
	}

using manipulator :: endLine;
using manipulator :: underline;
using manipulator :: mode;

	// prover :: Tree implementation
	bool
	Heap :: prove (const Time timeLimit)
	{
		Memory :: pile().memorizeState();
 		Expression_ :: clearCounter();
 		bool isProved = false;
 		assert (tree_ == NULL);
 		tree_ = new Tree_ (format_, subFormat_, question_);
 		tree_->init();
 		isProved = tree_->prove (timeLimit);
 		data_ = tree_->getData();
 		tree_->confirm();
 		tree_->commitSuicide();
 		tree_ = NULL;
 		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			deleteAggregateObject (question_);
 		}
 		Memory :: pile().recallState();
 		return isProved;
	}
	void
	Heap :: start (String& message)
	{
		Memory :: pile().memorizeState();
 		Expression_ :: clearCounter();
 		assert (tree_ == NULL);
 		tree_ = new Tree_ (format_, subFormat_, question_);
 		tree_->init();
 		tree_->start (message);
	}
	void
	Heap :: grow()
	{
		assert (tree_ != NULL);
		tree_->grow();
	}
	void
	Heap :: stop()
	{
		assert (tree_ != NULL);
		data_ = tree_->getData();
 		tree_->stop();
 		tree_->commitSuicide();
 		tree_ = NULL;
 		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			deleteAggregateObject (question_);
 		}
 		Memory :: pile().recallState();
	}
	void
	Heap :: info (String& string)
	{
		assert (tree_ != NULL);
 		tree_->info (string);
	}
	void
	Heap :: confirm()
	{
		assert (tree_ != NULL);
		tree_->confirm();
	}
	bool
	Heap :: isProved()
	{
		assert (tree_ != NULL);
		return tree_->isProved();
	}
	void
	Heap :: showVolume (String& string) const
	{
		assert (tree_ != NULL);
		tree_->showVolume (string);
	}
	void
	Heap :: showTiming (String& string) const
	{
		assert (tree_ != NULL);
		tree_->showTiming (string);
	}
	Data*
	Heap :: getData() const
	{
		if (data_ == NULL) {
			data_ = tree_->getData();
		}
		if (data_ != NULL) {
			return new Data (*data_);
		} else {
			return new Data();
		}
	}

using manipulator :: iterate;
using manipulator :: tab;
using manipulator :: space;

	// object :: Object implementation
	void
	Heap :: commitSuicide() {
		delete this;
	}
	Size_t
	Heap :: getVolume() const
	{
		Size_t volume = 0;
		volume += getAggregateVolume (tree_);
		volume += getAggregateVolume (data_);
		if (Config :: growUpMode() == Config :: GROW_UP_DETERMINED) {
			volume += getAggregateVolume (question_);
 		}
		return volume;
	}
	Size_t
	Heap :: getSizeOf() const {
		return sizeof (Heap);
	}
	void
	Heap :: show (String& string) const {
	}

	/****************************
	 *		Private members
	 ****************************/
}
}
}

#endif /*MDL_PROVER_TREE_HEAP_PROVER_TREE_HEAP_CPP_*/
