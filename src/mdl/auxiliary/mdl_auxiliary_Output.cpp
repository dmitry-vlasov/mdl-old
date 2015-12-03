/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_auxiliary_Output.cpp                                 */
/* Description:     output routines class                                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_AUXILIARY_OUTPUT_CPP_
#define MDL_AUXILIARY_OUTPUT_CPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/auxiliary/mdl_auxiliary.hpp"

namespace mdl {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	inline
	Output :: Output (const char* filePath) :
	fileStream_ (),
	filePath_ (filePath),
	buffer_ (INITIAL_OUTPUT_BUFFER_CAPACITY),
	objectCount_ (0) {
	}
	inline
	Output :: Output (const String& filePath) :
	fileStream_ (),
	filePath_ (filePath),
	buffer_ (INITIAL_OUTPUT_BUFFER_CAPACITY),
	objectCount_ (0) {
	}
	Output :: ~ Output() {
	}

using manipulator :: endLine;

	void
	Output :: open ()
	{
		const char* const
			outputPath = filePath_.c_str();
		fileStream_.open (outputPath, std :: ios :: binary);
		if (!fileStream_.is_open()) {
			Error* error = new Error (Error :: OUTPUT);
			error->message() << "cannot open file: " << filePath_ << " for output" << endLine;
			throw error;
		}
	}
	void
	Output :: close()
	{
		fileStream_ << buffer_;
		buffer_.clear();
		fileStream_.flush();
		fileStream_.close();
	}
	void
	Output :: write (const object :: Writable* const object)
	{
		if (Config :: translate()) {
			object->translate (buffer_);
		} else {
			object->replicate (buffer_);
		}
		fileStream_ << buffer_;
		buffer_.clear();

		objectCount_ ++;
		if (objectCount_ >= OUTPUT_FILE_FLUSH_COUNT_THRESHOLD) {
			fileStream_.flush();
			objectCount_ = 0;
		}
	}
	inline String&
	Output :: buffer() {
		return buffer_;
	}

	// nstd :: Object implementation
	void
	Output :: commitSuicide() {
		delete this;
	}
	Size_t
	Output :: getVolume() const
	{
		Size_t volume = 0;
		volume += filePath_.getVolume();
		volume += buffer_.getVolume();
		return volume;
	}
	Size_t
	Output :: getSizeOf() const {
		return sizeof (Output);
	}
	void
	Output :: show (nstd :: String<>&) const {
	}
}
}

#endif /*MDL_AUXILIARY_OUTPUT_CPP_*/
