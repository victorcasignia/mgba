/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#ifndef QGBA_COLOR_PICKER
#define QGBA_COLOR_PICKER

#include <QObject>

class QColor;
class QWidget;

namespace QGBA {

class ColorPicker : public QObject {
Q_OBJECT

public:
	ColorPicker();
	ColorPicker(QWidget* parent, const QColor& defaultColor);

	ColorPicker& operator=(const ColorPicker&);

signals:
	void colorChanged(const QColor&);

protected:
	bool eventFilter(QObject* obj, QEvent* event) override;

private:
	QWidget* m_parent = nullptr;
};

}

#endif
