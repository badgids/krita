/*
 *  SPDX-FileCopyrightText: 2024 Wolthera van Hövell tot Westerflier <griffinvalley@gmail.com>
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 */
import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.12
import org.krita.flake.text 1.0

TextPropertyBase {
    property int breakType;
    visible: properties.lineBreakState !== KoSvgTextPropertiesModel.PropertyUnset;

    onPropertiesUpdated: {
        blockSignals = true;
        breakType = properties.lineBreak;
        blockSignals = false;
    }

    onBreakTypeChanged: {
        lineBreakCmb.currentIndex = lineBreakCmb.indexOfValue(breakType)
        if (!blockSignals) {
            properties.lineBreak = breakType;
        }
    }

    RowLayout {
        spacing: columnSpacing;
        width: parent.width;

        RevertPropertyButton {
            id: revertLineBreak;
            revertEnabled: properties.lineBreakState === KoSvgTextPropertiesModel.PropertySet
        }

        Label {
            text: i18nc("@label:listbox", "Line Break:")
        }

        ComboBox {
            id: lineBreakCmb
            model: [
                { text: i18nc("@label:inlistbox", "Auto"), value: KoSvgText.LineBreakAuto},
                { text: i18nc("@label:inlistbox", "Loose"), value: KoSvgText.LineBreakLoose},
                { text: i18nc("@label:inlistbox", "Normal"), value: KoSvgText.LineBreakNormal},
                { text: i18nc("@label:inlistbox", "Strict"), value: KoSvgText.LineBreakStrict},
                { text: i18nc("@label:inlistbox", "Anywhere"), value: KoSvgText.LineBreakAnywhere}
            ]
            Layout.fillWidth: true;
            textRole: "text";
            valueRole: "value";
            onActivated: breakType = currentValue;
        }
    }
}
