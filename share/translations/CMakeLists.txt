#  Copyright (C) 2014 Felix Geyer <debfx@fobos.de>
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 2 or (at your option)
#  version 3 of the License.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.
FILE(GLOB TRANSLATION_FILES *.ts)
GET_FILENAME_COMPONENT(TRANSLATION_EN_ABS keepassx_en.ts ABSOLUTE)
LIST(REMOVE_ITEM TRANSLATION_FILES keepassx_en.ts)
LIST(REMOVE_ITEM TRANSLATION_FILES ${TRANSLATION_EN_ABS})
MESSAGE(STATUS "${TRANSLATION_FILES}")
QT6_ADD_TRANSLATION(QM_FILES ${TRANSLATION_FILES})
INSTALL(FILES ${QM_FILES} DESTINATION ${DATA_INSTALL_DIR}/translations)
ADD_CUSTOM_TARGET(translations DEPENDS ${QM_FILES})
ADD_DEPENDENCIES(${PROGNAME} translations)
