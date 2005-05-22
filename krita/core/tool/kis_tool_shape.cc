/*
 *  Copyright (c) 2005 Adrian Page
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#include <qwidget.h>
#include <qlayout.h>
#include <qcombobox.h>

#include <kdebug.h>
#include <klocale.h>

#include "kis_tool_shape.h"
#include "wdgshapeoptions.h"

KisToolShape::KisToolShape(const QString& UIName) : super(UIName)
{
	m_shapeOptionsWidget = 0;
	m_optionLayout = 0;
}

KisToolShape::~KisToolShape()
{
}

QWidget* KisToolShape::createOptionWidget(QWidget* parent)
{
	QWidget *widget = super::createOptionWidget(parent);

	m_shapeOptionsWidget = new WdgGeometryOptions(widget);
	Q_CHECK_PTR(m_shapeOptionsWidget);

	m_optionLayout = new QGridLayout(widget, 2, 1);
	super::addOptionWidgetLayout(m_optionLayout);

	m_optionLayout -> addWidget(m_shapeOptionsWidget, 0, 0);

	return widget;
}

void KisToolShape::addOptionWidgetLayout(QLayout *layout)
{
	Q_ASSERT(m_optionLayout != 0);

	m_optionLayout -> addMultiCellLayout(layout, 1, 1, 0, 1);
}

KisPainter::FillStyle KisToolShape::fillStyle(void)
{
	if (m_shapeOptionsWidget) {
		return static_cast<KisPainter::FillStyle>(m_shapeOptionsWidget -> cmbFill -> currentItem());
	} else {
		return KisPainter::FillStyleNone;
	}
}

#include "kis_tool_shape.moc"

