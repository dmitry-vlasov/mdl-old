/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_Contents.cpp                                    */
/* Description:     contents of a theory                                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_FORM_CONTENTS_CPP_
#define MDL_FORM_CONTENTS_CPP_

namespace mdl {
namespace form {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Contents :: Contents
	(
		const Location& location,
		const mdl :: Comments* const comments,
		const value :: Name name,
		mdl :: Theory* theory
	) :
	form :: Identifiable (location, comments, name, theory),
	innerTheory_ (NULL),
	componentVector_  (INITIAL_COMPONENT_VECTOR_CAPACITY),
	firstPassVector_  (INITIAL_COMPONENT_VECTOR_CAPACITY),
	secondPassVector_ (INITIAL_COMPONENT_VECTOR_CAPACITY),
	thirdPassVector_  (INITIAL_COMPONENT_VECTOR_CAPACITY),
	isVerified_ (false)
	{
		if (Config :: localParsing()) {
			return;
		}
		const index :: Form
			index = form :: Identifiable :: theory_->getIndex (identificator_);
		if  (index == index :: undefined :: FORM) {
			Error* error = new Error (location_, Error :: SEMANTIC, "undeclared theory:");
			error->message() << *identificator_ << endLine;
			throw error;
		}
		innerTheory_ = Math :: theories()->get (index);
		if (innerTheory_ == NULL) {
			Error* error = new Error (location_, Error :: SEMANTIC, "undeclared theory:");
			error->message() << *identificator_ << endLine;
			throw error;
		}
	}
	Contents :: ~ Contents() {
	}

	// mdl :: Components implementation
	void
	Contents :: addComponentLast (object :: Verifiable* component)
	{
		componentVector_.add (component);
		component->setContents (this);
		if (dynamic_cast<mdl :: Proof*>(component) != NULL) {
			secondPassVector_.add (component);
		} else if (dynamic_cast<mdl :: Evaluation*>(component) != NULL) {
			thirdPassVector_.add (component);
		} else {
			firstPassVector_.add (component);
		}
	}
	void
	Contents :: addComponentNextTo
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
		component->setContents (this);
		if (dynamic_cast<mdl :: Proof*>(component) != NULL) {
			secondPassVector_.add (component);
		} else if (dynamic_cast<mdl :: Evaluation*>(component) != NULL) {
			thirdPassVector_.add (component);
		} else {
			firstPassVector_.add (component);
		}
	}
	index :: Assertion
	Contents :: getSize() const {
		return componentVector_.getSize();
	}
	object :: Verifiable*
	Contents :: getComponent (const index :: Assertion i) {
		return componentVector_.getValue (i);
	}
	const object :: Verifiable*
	Contents :: getComponent (const index :: Assertion i) const {
		return componentVector_.getValue (i);
	}

using manipulator :: endLine;
using manipulator :: space;
using manipulator :: iterate;
using manipulator :: tab;

	// object :: Verifiable implementation
	void
	Contents :: check()
	{
		isVerified_ = false;
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			checkSingleThreaded();
		} else {
			checkSingleThreaded();
			//doJobThreaded (checkInThread, &secondPassVector_);
		}
		#else
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->check();
		}
		#endif
		isVerified_ = true;
	}
	void
	Contents :: compress()
	{
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->compress();
		}
	}
	void
	Contents :: reprove()
	{
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->reprove();
		}
	}
	void
	Contents :: prove()
	{
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable*
				component = componentVector_.getValue (i);
			component->prove();
		}
	}
	bool
	Contents :: isVerified() const {
		return isVerified_;
	}
	void
	Contents :: mine (String& string) const
	{
		value :: Integer depth = Identifiable :: getDepth();
		string << iterate << depth << tab;
		string << "<contents ";
		Identifiable :: mine (string);
		string << ">" << endLine;
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->mine (string);
		}
		string << iterate << depth << tab;
		string << "</contents>" << endLine;
	}

	// object :: Buildable implementation
	void
	Contents :: build()
	{
		#ifdef MULTY_THREADED
		if (Config :: getConcurrency (Config :: THREADS) == 1) {
			buildSingleThreaded();
		} else {
			doJobThreaded (buildInThread, &firstPassVector_);
			doJobThreaded (buildInThread, &secondPassVector_);
			doJobThreaded (buildInThread, &thirdPassVector_);
		}
		#else
		buildSingleThreaded();
		#endif
	}

	// object :: Writable implementation
	void
	Contents :: translate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->translate (string);
			string << endLine;
		}
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable*
				component = componentVector_.getValue (i);
			component->translate (string);
		}
	}
	void
	Contents :: replicate (String& string) const
	{
		if (!Config :: removeComments() && (comments_ != NULL)) {
			string << location_.getIndent();
			comments_->replicate (string);
			string << endLine;
		}
		string << location_.getIndent();
		string << mdl :: Token :: contents_ << space;
		string << mdl :: Token :: of_ << space;
		form :: Identifiable :: replicateName (string);
		string << space << Token :: openBrace_ << endLine;
		string << endLine;

		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable*
				component = componentVector_.getValue (i);
			component->replicate (string);
		}
		string << location_.getIndent();
		string << Token :: closeBrace_ << endLine;
		string << endLine;
	}
	void
	Contents :: write (Output& output) const
	{
		if (!Config :: translate()) {
			if (!Config :: removeComments() && (comments_ != NULL)) {
				output.buffer() << location_.getIndent();
				comments_->replicate (output.buffer());
				output.buffer() << endLine;
			}
			output.buffer() << location_.getIndent();
			output.buffer() << mdl :: Token :: contents_ << space;
			output.buffer() << mdl :: Token :: of_ << space;
			form :: Identifiable :: replicateName (output.buffer());
			output.buffer() << space << Token :: openBrace_ << endLine;
			output.buffer() << endLine;
		}

		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			const object :: Verifiable*
				component = componentVector_.getValue (i);
			component->write (output);
		}
		if (!Config :: translate()) {
			output.buffer() << location_.getIndent();
			output.buffer() << Token :: closeBrace_ << endLine;
			output.buffer() << endLine;
		}
	}
	bool
	Contents :: lookup() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			if (Config :: lookupDefinition()) {
				std :: cout << *innerTheory_;
			} else {
				std :: cout << innerTheory_->getLocation();
			}
			return true;
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
	Contents :: find()
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
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
	Contents :: find() const
	{
		if (location_.isNearestTo (Config :: getPosition())) {
			return this;
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
	Contents :: commitSuicide() {
		delete this;
	}
	Size_t
	Contents :: getVolume() const {
		Size_t volume = 0;
		volume += form :: Identifiable :: getVolume();
		volume += componentVector_.getVolume();
		volume += firstPassVector_.getVolume();
		volume += secondPassVector_.getVolume();
		volume += thirdPassVector_.getVolume();
		return volume;
	}
	Size_t
	Contents :: getSizeOf() const {
		return sizeof (Contents);
	}

	/****************************
	 *		Private members
	 ****************************/

	void
	Contents :: checkSingleThreaded()
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
	Contents :: buildSingleThreaded()
	{
		for (value :: Integer i = 0; i < componentVector_.getSize(); ++ i) {
			object :: Verifiable* const
				component = componentVector_.getValue (i);
			component->build();
		}
	}

#ifdef MULTY_THREADED
	void
	Contents :: doJobThreaded (void* func (void*), const VerifiableVector_* vector)
	{
		const value :: Integer threadCount = Config :: getConcurrency (Config :: THREADS);
		pthread_t  threads [threadCount];
		Arguments_ arguments [threadCount];
		for (int i = 0; i < threadCount; ++ i) {
			arguments [i].threadIndex_ = i;
			arguments [i].threadCount_ = threadCount;
			arguments [i].vector_ = vector;
			pthread_create (threads + i, NULL, func, reinterpret_cast<void*>(arguments + i));
		}
		Error* error = NULL;
		for (int i = 0; i < threadCount; ++ i) {
			Error* err = NULL;
			pthread_join (threads [i], reinterpret_cast<void**>(&err));
			if (err != NULL) {
				err->setNext (error);
				error = err;
			}
		}
		if (error != NULL) {
			throw error;
		}
	}
#endif

	/**********************
	 *		Functions
	 **********************/

#ifdef MULTY_THREADED
	void* checkInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		Contents :: Arguments_* arguments = reinterpret_cast<Contents :: Arguments_*>(pointer);
		const value :: Integer threadCount = arguments->threadCount_;
		for (value :: Integer i = 0; i < arguments->vector_->getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			object :: Verifiable* component = arguments->vector_->getValue (i);
			try {
				component->check();
			} catch (Error* e) {
				error = e;
				break;
			} catch (std :: exception& exception) {
				error = new Error (Error :: SEMANTIC, exception.what());
				break;
			} catch (...) {
				error = new Error (Error :: SEMANTIC, "unknown exception.");
				break;
			}
		}
		Memory :: pile().releaseThread();
		return error;
	}
	void* buildInThread (void* pointer)
	{
		Error* error = NULL;
		Memory :: pile().registerThread();
		Contents :: Arguments_* arguments = reinterpret_cast<Contents :: Arguments_*>(pointer);
		const value :: Integer threadCount = arguments->threadCount_;
		for (value :: Integer i = 0; i < arguments->vector_->getSize(); ++ i) {
			if (i % threadCount != arguments->threadIndex_) {
				continue;
			}
			object :: Verifiable* component = arguments->vector_->getValue (i);
			try {
				component->build();
			} catch (Error* e) {
				error = e;
				break;
			} catch (std :: exception& exception) {
				error = new Error (Error :: SEMANTIC, exception.what());
				break;
			} catch (...) {
				error = new Error (Error :: SEMANTIC, "unknown exception.");
				break;
			}
		}
		Memory :: pile().releaseThread();
		return error;
	}
#endif
}
}

#endif /*MDL_FORM_CONTENTS_CPP_*/
