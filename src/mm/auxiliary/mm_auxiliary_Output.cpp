/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Output.cpp                                  */
/* Description:     class for output routines                                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"
#include "auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

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
	Output :: open()
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
	String&
	Output :: buffer() {
		return buffer_;
	}
	void
	Output :: write (const object :: Writable* const object)
	{
		object->write (buffer_);

		fileStream_ << buffer_;
		buffer_.clear();

		objectCount_ ++;
		if (objectCount_ >= OUTPUT_FILE_FLUSH_COUNT_THRESHOLD) {
			fileStream_.flush();
			objectCount_ = 0;
		}
	}

using manipulator :: endLine;

	// object :: Object implementation
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
	Output :: show (String&) const {
	}
}
}


