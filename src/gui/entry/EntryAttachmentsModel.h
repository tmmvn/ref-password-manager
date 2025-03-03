/*
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
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
#ifndef KEEPASSX_ENTRYATTACHMENTSMODEL_H
#define KEEPASSX_ENTRYATTACHMENTSMODEL_H
#include <QAbstractListModel>
class EntryAttachments;

class EntryAttachmentsModel final:public QAbstractListModel
{
	Q_OBJECT public:
	explicit EntryAttachmentsModel(
		QObject* parent = nullptr
	);
	void setEntryAttachments(
		EntryAttachments* entry
	);
	virtual int rowCount(
		const QModelIndex &parent = QModelIndex()
	) const override;
	virtual int columnCount(
		const QModelIndex &parent = QModelIndex()
	) const override;
	virtual QVariant data(
		const QModelIndex &index,
		int role = Qt::DisplayRole
	) const override;
	QString keyByIndex(
		const QModelIndex &index
	) const;
private Q_SLOTS:
	void do_attachmentChange(
		const QString &key
	);
	void do_attachmentAboutToAdd(
		const QString &key
	);
	void do_attachmentAdd();
	void do_attachmentAboutToRemove(
		const QString &key
	);
	void do_attachmentRemove();
	void do_aboutToReset();
	void do_reset();
private:
	EntryAttachments* entryAttachments;
};
#endif // KEEPASSX_ENTRYATTACHMENTSMODEL_H
