/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Source.cpp                                      */
/* Description:     source class                                             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_SOURCE_CPP_
#define MDL_FORM_SOURCE_CPP_

#include "mdl/math/mdl_math.hpp"
#include "mdl/form/mdl_form_Source.hpp"

#include "smm/auxiliary/smm_auxiliary_Config.hpp"

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Source :: Source
	(
		bool isTop,
		Lexer* lexer,
		const mdl :: Comments* comments,
		const Path* sourcePath
	) :
	isTop_ (isTop),
	lexer_ (lexer),
	sourcePath_ (new Path (*sourcePath)),
	targetPath_ (NULL),
	comments_ (comments),
	componentVector_ (INITIAL_COMPONENT_VECTOR_CAPACITY),
	isVerified_ (false)
	{
		if (Config :: useWriting()) {
			computeTargetPath();
		}
		if (isTop_) {
			if (source_ != NULL) {
				source_->commitSuicide();
			}
			source_ = this;
		}
	}
	Source :: ~ Source()
	{
		deleteAggregateObject (sourcePath_);
		deleteAggregateObject (targetPath_);
		deleteAggregateObject (lexer_);
		deleteAggregateObject (comments_);
		if (isTop_) {
			source_ = NULL;
		}
	}

	inline Source*
	Source :: get() {
		return source_;
	}
	void
	Source :: clear()
	{
		if (source_ != NULL) {
			source_->commitSuicide();
			source_ = NULL;
		}
	}
	void
	Source :: release()
	{
		if (source_ != NULL) {
			source_->commitSuicide();
			source_ = NULL;
		}
	}

using manipulator :: endLine;

	// mdl :: Source implementation
	void
	Source :: mine() const
	{
		if (!isTop_) {
			return;
		}
		String mineOutput (INITIAL_MINE_OUTPUT_CAPACITY);
		mineOutput << "<!DOCTYPE russell_mining_output>" << endLine;
		mineOutput << "<outline>" << endLine;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->mine (mineOutput);
		}
		mineOutput << "</outline>" << endLine;
		std :: cout << mineOutput << std :: endl;
	}

	// mdl :: Components implementation
	void
	Source :: addComponentLast (object :: Verifiable* component) {
		componentVector_.add (component);
	}
	void
	Source :: addComponentNextTo
	(
		object :: Verifiable* component,
		const object :: Verifiable* sibling
	)
	{
		value :: Integer index = value :: undefined :: INTEGER;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable*
				component = componentVector_.getValue (i);
			if (component == sibling) {
				index = i;
				break;
			}
		}
		if (index == value :: undefined :: INTEGER) {
			componentVector_.add (component);
		} else {
			componentVector_.insert (component, index + 1);
		}
	}
	index :: Assertion
	Source :: getSize() const {
		return componentVector_.getSize();
	}
	object :: Verifiable*
	Source :: getComponent (const index :: Assertion i) {
		return componentVector_.getValue (i);
	}
	const object :: Verifiable*
	Source :: getComponent (const index :: Assertion i) const {
		return componentVector_.getValue (i);
	}

	// object :: Verifiable implementation
	void
	Source :: check()
	{
		isVerified_ = false;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->check();
		}
		isVerified_ = true;
	}
	void
	Source :: compress()
	{
		isVerified_ = false;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->compress();
		}
	}
	void
	Source :: reprove()
	{
		isVerified_ = false;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->reprove();
		}
	}
	void
	Source :: prove()
	{
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->prove();
		}
	}
	bool
	Source :: isVerified() const {
		return isVerified_;
	}

	// object :: Buildable implementation
	void
	Source :: build()
	{
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->build();
		}
	}

	// object :: Writable implementation
	void
	Source :: translate (String& string) const {
	}
	void
	Source :: replicate (String& string) const
	{
		if (comments_ != NULL) {
			comments_->replicate (string);
		}
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->replicate (string);
		}
	}
	void
	Source :: write() const
	{
		if (!isTop_ && !Config :: deepWrite()) {
			return;
		}
		const String& file = targetPath_->getString();
		targetPath_->provideDirectory();
		Output output (file);
		output.open();
		if (comments_ != NULL) {
			if (Config :: translate()) {
				comments_->translate (output.buffer());
			} else {
				comments_->replicate (output.buffer());
			}
			output.buffer() << endLine;
		}
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->write();
			component->write (output);
		}
		output.close();
	}
	bool
	Source :: lookup() const
	{
		if (!isTop_) {
			return false;
		}
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable*
				component = componentVector_.getValue (i);
			if (component->lookup()) {
				return true;
			}
		}
		return false;
	}
	object :: Writable*
	Source :: find()
	{
		if (!isTop_) {
			return NULL;
		}
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			object :: Writable*
				object = component->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}
	const object :: Writable*
	Source :: find() const
	{
		if (!isTop_) {
			return NULL;
		}
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable* const
				component = componentVector_.getValue (i);
			const object :: Writable*
				object = component->find();
			if (object != NULL) {
				return object;
			}
		}
		return NULL;
	}

	// object :: Object implementation
	void
	Source :: commitSuicide() {
		delete this;
	}
	Size_t
	Source :: getSizeOf() const {
		return sizeof (Source);
	}
	Size_t
	Source :: getVolume() const
	{
		Size_t volume = 0;
		volume += componentVector_.getVolume();
		volume += getAggregateVolume (sourcePath_);
		volume += getAggregateVolume (targetPath_);
		volume += getAggregateVolume (lexer_);
		volume += getAggregateVolume (comments_);
		if (isTop_) {
			volume += getSizeOf();
		}
		return volume;
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Source :: computeTargetPath()
	{
		if (isTop_) {
			if (Config :: runOnefold()) {
				if (Config :: getTarget().isUndefined()) {
					Error* error = new Error (Error :: SEMANTIC, "no output path.");
					throw error;
				}
				targetPath_ = new Path (Config :: getTarget());
			} else {
				if (Config :: getTarget().isDefined()) {
					targetPath_ = new Path (Config :: getTarget());
				}
			}
		} else {
			typedef const nstd :: Path<> Path_;
			typedef Path_ :: String_ String_;

			targetPath_ = new Path (*sourcePath_);

			const Path_& sourceRoot = Config :: getSource();
			for (int d = 0; d < sourceRoot.getDepth(); ++ d) {
				String* dir = targetPath_->popDirectoryFirst();
				delete dir;
			}
			const Path_& targetRoot = Config :: getTarget();
			for (int i = 0; i < targetRoot.getDepth(); ++ i) {
				const int d = targetRoot.getDepth() - i - 1;
				const String_& dir = targetRoot.getDirectory (d);
				targetPath_->pushDirectoryFirst (dir);
			}
			targetPath_->prefix() = targetRoot.getPrefix();
		}
		if (Config :: translate()) {
			targetPath_->extension() = smm :: Config :: smmExtension();
		} else {
			targetPath_->extension() = mdl :: Config :: russellExtension();
		}
	}

	/***********************************
	 *		Private static attributes
	 ***********************************/

	Source* Source :: source_;
}
}

#endif /*MDL_FORM_SOURCE_CPP_*/
