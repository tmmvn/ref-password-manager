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
#include "TestDeletedObjects.h"
#include <QTest>
#include "core/Database.h"
#include "core/Group.h"
#include "crypto/Crypto.h"
#include "format/KeePass2XmlReader.h"
#include "config-keepassx-tests.h"
QTEST_GUILESS_MAIN(
	TestDeletedObjects
)

void TestDeletedObjects::initTestCase()
{
	QVERIFY(
		Crypto::init()
	);
}

void TestDeletedObjects::createAndDelete(
	Database* db,
	int delObjectsSize
)
{
	QCOMPARE(
		db->getDeletedObjects().size(),
		delObjectsSize
	);
	Group* root = db->getRootGroup();
	int rootChildrenCount = root->getChildren().size();
	Group* g = new Group();
	g->setParent(
		root
	);
	UUID gUuid = UUID::random();
	g->setUuid(
		gUuid
	);
	delete g;
	QCOMPARE(
		db->getDeletedObjects().size(),
		++delObjectsSize
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-1).uuid,
		gUuid
	);
	QCOMPARE(
		rootChildrenCount,
		root->getChildren().size()
	);
	Group* g1 = new Group();
	g1->setParent(
		root
	);
	UUID g1Uuid = UUID::random();
	g1->setUuid(
		g1Uuid
	);
	Entry* e1 = new Entry();
	e1->setGroup(
		g1
	);
	UUID e1Uuid = UUID::random();
	e1->setUUID(
		e1Uuid
	);
	Group* g2 = new Group();
	g2->setParent(
		g1
	);
	UUID g2Uuid = UUID::random();
	g2->setUuid(
		g2Uuid
	);
	Entry* e2 = new Entry();
	e2->setGroup(
		g2
	);
	UUID e2Uuid = UUID::random();
	e2->setUUID(
		e2Uuid
	);
	delete g1;
	delObjectsSize += 4;
	QCOMPARE(
		db->getDeletedObjects().size(),
		delObjectsSize
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-4).uuid,
		e1Uuid
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-3).uuid,
		e2Uuid
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-2).uuid,
		g2Uuid
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-1).uuid,
		g1Uuid
	);
	QCOMPARE(
		rootChildrenCount,
		root->getChildren().size()
	);
	Entry* e3 = new Entry();
	e3->setGroup(
		root
	);
	UUID e3Uuid = UUID::random();
	e3->setUUID(
		e3Uuid
	);
	delete e3;
	QCOMPARE(
		db->getDeletedObjects().size(),
		++delObjectsSize
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-1).uuid,
		e3Uuid
	);
	QCOMPARE(
		rootChildrenCount,
		root->getChildren().size()
	);
}

void TestDeletedObjects::testDeletedObjectsFromFile()
{
	KeePass2XmlReader reader;
	reader.setStrictMode(
		true
	);
	QString xmlFile = QString(
		KEEPASSX_TEST_DATA_DIR
	).append(
		"/NewDatabase.xml"
	);
	Database* db = reader.readDatabase(
		xmlFile
	);
	createAndDelete(
		db,
		2
	);
	delete db;
}

void TestDeletedObjects::testDeletedObjectsFromNewDb()
{
	Database* db = new Database();
	createAndDelete(
		db,
		0
	);
	delete db;
}

void TestDeletedObjects::testDatabaseChange()
{
	Database* db = new Database();
	Group* root = db->getRootGroup();
	int delObjectsSize = 0;
	Database* db2 = new Database();
	Group* root2 = db2->getRootGroup();
	int delObjectsSize2 = 0;
	Entry* e = new Entry();
	e->setGroup(
		root
	);
	QCOMPARE(
		db->getDeletedObjects().size(),
		delObjectsSize
	);
	QCOMPARE(
		db2->getDeletedObjects().size(),
		delObjectsSize2
	);
	e->setGroup(
		root2
	);
	QCOMPARE(
		db->getDeletedObjects().size(),
		++delObjectsSize
	);
	QCOMPARE(
		db2->getDeletedObjects().size(),
		delObjectsSize2
	);
	delete e;
	QCOMPARE(
		db->getDeletedObjects().size(),
		delObjectsSize
	);
	QCOMPARE(
		db2->getDeletedObjects().size(),
		++delObjectsSize2
	);
	Group* g1 = new Group();
	g1->setParent(
		root
	);
	UUID g1Uuid = UUID::random();
	g1->setUuid(
		g1Uuid
	);
	Entry* e1 = new Entry();
	e1->setGroup(
		g1
	);
	UUID e1Uuid = UUID::random();
	e1->setUUID(
		e1Uuid
	);
	g1->setParent(
		root2
	);
	delObjectsSize += 2;
	QCOMPARE(
		db->getDeletedObjects().size(),
		delObjectsSize
	);
	QCOMPARE(
		db2->getDeletedObjects().size(),
		delObjectsSize2
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-2).uuid,
		e1Uuid
	);
	QCOMPARE(
		db->getDeletedObjects().at(delObjectsSize-1).uuid,
		g1Uuid
	);
	Group* group = new Group();
	Entry* entry = new Entry();
	entry->setGroup(
		group
	);
	entry->setGroup(
		root
	);
	QCOMPARE(
		db->getDeletedObjects().size(),
		delObjectsSize
	);
	QCOMPARE(
		db2->getDeletedObjects().size(),
		delObjectsSize2
	);
	delete group;
	delete db;
	delete db2;
}
