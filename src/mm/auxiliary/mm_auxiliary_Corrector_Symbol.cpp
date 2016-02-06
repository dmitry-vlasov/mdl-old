/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_auxiliary_Corrector_Symbol.cpp                        */
/* Description:     corrector for math.mm symbol designations                */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include <iostream>

#include "mm/lexer/mm_lexer.hpp"
#include "mm/auxiliary/mm_auxiliary.hpp"

namespace mm {
namespace auxiliary {

	/****************************
	 *		Public members
	 ****************************/

	void
	Corrector :: Symbol :: release()
	{
		deleteAggregateObject (path_);
		deleteAggregateObject (ascii_);
		deleteAggregateObject (unicode_);
		deleteAggregateObject (latex_);
		deleteAggregateObject (buffer_);
	}

	// nstd :: Static implementation
	void
	Corrector :: Symbol :: initRaw()
	{
		if (Config :: useSymbolCorrection()) {
			path_ =  new Path (*Config :: getSymbolCorrectionSource());
			ascii_ = new Vector_ (INITIAL_VECTOR_CAPACITY);
			unicode_ = new Vector_ (INITIAL_VECTOR_CAPACITY);
			latex_ = new Vector_ (INITIAL_VECTOR_CAPACITY);
			run();
		}
	}
	void
	Corrector :: Symbol :: showRaw (String&) {
	}
	Size_t
	Corrector :: Symbol :: getRawVolume()
	{
		Size_t result = 0;
		result += getAggregateVolume (path_);
		result += getAggregateVolume (ascii_);
		result += getAggregateVolume (unicode_);
		result += getAggregateVolume (latex_);
		result += getAggregateVolume (buffer_);
		return result;
	}

	/****************************
	 *		Private members
	 ****************************/

using manipulator :: endLine;

	void
	Corrector :: Symbol :: run()
	{
		try {
			read();
			parse();
		} catch (Error* error) {
			std :: cout << error->message() << std :: endl;
			delete error;
		} catch (std :: exception& e) {
			std :: cout << "exception: " << e.what() << std :: endl;
		}
	}
	void
	Corrector :: Symbol :: read()
	{
		const char* file = path_->getString().c_str();
		const Size_t fileSize = system :: getFileSize (file);
		if (fileSize == Undefined<Size_t> :: getValue()) {
			Error* error = new Error (Error :: INPUT);
			error->message() << "symbol correction file ";
			error->message() << file << " does not exist or is empty." << endLine;
			throw error;
		}
		buffer_ = new String (fileSize + 1);
		fileStream_.open (file, std :: ios :: binary);
		fileStream_.read (buffer_->c_str(), fileSize);
		buffer_->getReference (fileSize) = chars :: NULL_CHAR;
		fileStream_.close();
	}
	void
	Corrector :: Symbol :: parse()
	{
		const char* buffer = buffer_->c_str();
		while (*buffer != chars :: NULL_CHAR) {
			consumeToken ("symbol\n", buffer);
			const String*
				ascii = parseEntry ("\tascii", ascii_, buffer);
			++ buffer;
			const String*
				unicode = parseEntry ("\tunicode", unicode_, buffer);
			++ buffer;
			const String*
				latex = parseEntry ("\tlatex", ascii_, buffer);
			++ buffer;
			Table :: literals()->addTriple (*ascii, unicode, latex);
		}
	}
	void
	Corrector :: Symbol :: consumeToken (const char* token, const char*& buffer)
	{
		const char* begin = buffer;
		for (
				const char* str = token;
				*str != chars :: NULL_CHAR;
				str ++
			)
		{
			const char ch = *buffer;
			++ buffer;
			if (*str != ch) {
				parseError (token, begin);
			}
		}
	}
	const char*
	Corrector :: Symbol :: consumeString (const char*& buffer)
	{
		const char* begin = buffer;
		while (*buffer != chars :: NEW_LINE) {
			++ buffer;
			if (*buffer == chars :: NULL_CHAR) {
				parseError ("null char", begin);
			}
		}
		return buffer;
	}
	const String*
	Corrector :: Symbol :: parseEntry (const char* token, Vector_* place, const char*& buffer)
	{
		consumeToken (token, buffer);
		const char* begin = buffer + 1;
		const char* end = consumeString (buffer);
		String* string = place->push();
		string->copyFrom (begin, end);
		return string;
	}
	void
	Corrector :: Symbol :: parseError (const char* token, const char* buffer)
	{
		Error* error = new Error (Error :: INPUT);
		error->message() << "syntax error in symbol correction file " << path_->getString() << endLine;
		error->message() << "token \"" << token << "\" expected," << endLine;
		error->message() << "buffer: "<< endLine;
		error->message() << buffer << endLine;
		throw error;
	}

	/*************************************
	 *		Private static attributes
	 *************************************/

	Path*
		Corrector :: Symbol :: path_ = NULL;
	Corrector :: Symbol :: Vector_*
		Corrector :: Symbol :: ascii_ = NULL;
	Corrector :: Symbol :: Vector_*
		Corrector :: Symbol :: unicode_ = NULL;
	Corrector :: Symbol :: Vector_*
		Corrector :: Symbol :: latex_ = NULL;
	InputFileStream
		Corrector :: Symbol :: fileStream_;
	String*
		Corrector :: Symbol :: buffer_ = NULL;
}
}


