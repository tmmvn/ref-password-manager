/*
 *  Copyright (C) 2010 Felix Geyer <debfx@fobos.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KEEPASSX_SYMMETRICCIPHERSTREAM_H
#define KEEPASSX_SYMMETRICCIPHERSTREAM_H
#include <QByteArray>
#include "crypto/SymmetricCipher.h"
#include "streams/LayeredStream.h"

class SymmetricCipherStream final:public LayeredStream
{
	Q_OBJECT public:
	SymmetricCipherStream(
		QIODevice* baseDevice,
		SymmetricCipher::Algorithm algo,
		SymmetricCipher::Mode mode,
		SymmetricCipher::Direction direction
	);
	virtual ~SymmetricCipherStream() override;
	bool init(
		const QByteArray &key,
		const QByteArray &iv
	);
	virtual bool open(
		OpenMode mode
	) override;
	virtual bool reset() override;
	virtual void close() override;
protected:
	virtual qint64 readData(
		char* data,
		qint64 maxSize
	) override;
	virtual qint64 writeData(
		const char* data,
		qint64 maxSize
	) override;
private:
	void resetInternalState();
	bool readBlock();
	bool writeBlock(
		bool lastBlock
	);
	const QScopedPointer<SymmetricCipher> cipher;
	QByteArray buffer;
	int bufferPos;
	bool bufferFilling;
	bool error;
	bool isInitalized;
	bool dataWritten;
};
#endif // KEEPASSX_SYMMETRICCIPHERSTREAM_H
