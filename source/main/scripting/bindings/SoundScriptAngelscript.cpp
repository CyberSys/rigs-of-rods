/*
    This source file is part of Rigs of Rods
    Copyright 2023 Petr Ohlidal

    For more information, see http://www.rigsofrods.org/

    Rigs of Rods is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3, as
    published by the Free Software Foundation.

    Rigs of Rods is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Rigs of Rods. If not, see <http://www.gnu.org/licenses/>.
*/

/// @file
/// @author Petr Ohlidal

#include "ScriptEngine.h"
#include "SoundScriptManager.h"

using namespace RoR;
using namespace AngelScript;

void RoR::RegisterSoundScript(AngelScript::asIScriptEngine* engine)
{
    int result = 0;

    // enum SoundTriggers
    result = engine->RegisterEnum("SoundTriggers"); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_NONE", SS_TRIG_NONE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_ENGINE", SS_TRIG_ENGINE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE1", SS_TRIG_AEROENGINE1); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE2", SS_TRIG_AEROENGINE2); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE3", SS_TRIG_AEROENGINE3); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE4", SS_TRIG_AEROENGINE4); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_HORN", SS_TRIG_HORN); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_BRAKE", SS_TRIG_BRAKE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_PUMP", SS_TRIG_PUMP); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_STARTER", SS_TRIG_STARTER); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TURBOBOV", SS_TRIG_TURBOBOV); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TURBOWASTEGATE", SS_TRIG_TURBOWASTEGATE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TURBOBACKFIRE", SS_TRIG_TURBOBACKFIRE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_ALWAYSON", SS_TRIG_ALWAYSON); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_REPAIR", SS_TRIG_REPAIR); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AIR", SS_TRIG_AIR); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_APDISCONNECT", SS_TRIG_GPWS_APDISCONNECT); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_10", SS_TRIG_GPWS_10); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_20", SS_TRIG_GPWS_20); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_30", SS_TRIG_GPWS_30); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_40", SS_TRIG_GPWS_40); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_50", SS_TRIG_GPWS_50); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_100", SS_TRIG_GPWS_100); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_PULLUP", SS_TRIG_GPWS_PULLUP); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GPWS_MINIMUMS", SS_TRIG_GPWS_MINIMUMS); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AIR_PURGE", SS_TRIG_AIR_PURGE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_SHIFT", SS_TRIG_SHIFT); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_GEARSLIDE", SS_TRIG_GEARSLIDE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_CREAK", SS_TRIG_CREAK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_BREAK", SS_TRIG_BREAK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_SCREETCH", SS_TRIG_SCREETCH); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_PARK", SS_TRIG_PARK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER1", SS_TRIG_AFTERBURNER1); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER2", SS_TRIG_AFTERBURNER2); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER3", SS_TRIG_AFTERBURNER3); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER4", SS_TRIG_AFTERBURNER4); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER5", SS_TRIG_AFTERBURNER5); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER6", SS_TRIG_AFTERBURNER6); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER7", SS_TRIG_AFTERBURNER7); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AFTERBURNER8", SS_TRIG_AFTERBURNER8); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE5", SS_TRIG_AEROENGINE5); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE6", SS_TRIG_AEROENGINE6); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE7", SS_TRIG_AEROENGINE7); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AEROENGINE8", SS_TRIG_AEROENGINE8); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AOA", SS_TRIG_AOA); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_IGNITION", SS_TRIG_IGNITION); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_REVERSE_GEAR", SS_TRIG_REVERSE_GEAR); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TURN_SIGNAL", SS_TRIG_TURN_SIGNAL); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TURN_SIGNAL_TICK", SS_TRIG_TURN_SIGNAL_TICK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TURN_SIGNAL_WARN_TICK", SS_TRIG_TURN_SIGNAL_WARN_TICK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_ALB_ACTIVE", SS_TRIG_ALB_ACTIVE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_TC_ACTIVE", SS_TRIG_TC_ACTIVE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT01", SS_TRIG_AVICHAT01); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT02", SS_TRIG_AVICHAT02); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT03", SS_TRIG_AVICHAT03); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT04", SS_TRIG_AVICHAT04); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT05", SS_TRIG_AVICHAT05); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT06", SS_TRIG_AVICHAT06); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT07", SS_TRIG_AVICHAT07); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT08", SS_TRIG_AVICHAT08); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT09", SS_TRIG_AVICHAT09); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT10", SS_TRIG_AVICHAT10); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT11", SS_TRIG_AVICHAT11); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT12", SS_TRIG_AVICHAT12); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_AVICHAT13", SS_TRIG_AVICHAT13); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("SoundTriggers", "SS_TRIG_LINKED_COMMAND", SS_TRIG_LINKED_COMMAND); ROR_ASSERT(result >= 0);

    // enum ModulationSources
    result = engine->RegisterEnum("ModulationSources"); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_NONE", SS_MOD_NONE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_ENGINE", SS_MOD_ENGINE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_TURBO", SS_MOD_TURBO); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE1", SS_MOD_AEROENGINE1); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE2", SS_MOD_AEROENGINE2); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE3", SS_MOD_AEROENGINE3); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE4", SS_MOD_AEROENGINE4); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_WHEELSPEED", SS_MOD_WHEELSPEED); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_INJECTOR", SS_MOD_INJECTOR); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_TORQUE", SS_MOD_TORQUE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_GEARBOX", SS_MOD_GEARBOX); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_CREAK", SS_MOD_CREAK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_BREAK", SS_MOD_BREAK); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_SCREETCH", SS_MOD_SCREETCH); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_PUMP", SS_MOD_PUMP); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE1", SS_MOD_THROTTLE1); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE2", SS_MOD_THROTTLE2); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE3", SS_MOD_THROTTLE3); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE4", SS_MOD_THROTTLE4); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE5", SS_MOD_THROTTLE5); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE6", SS_MOD_THROTTLE6); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE7", SS_MOD_THROTTLE7); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_THROTTLE8", SS_MOD_THROTTLE8); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE5", SS_MOD_AEROENGINE5); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE6", SS_MOD_AEROENGINE6); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE7", SS_MOD_AEROENGINE7); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AEROENGINE8", SS_MOD_AEROENGINE8); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AIRSPEED", SS_MOD_AIRSPEED); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_AOA", SS_MOD_AOA); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_LINKED_COMMANDRATE", SS_MOD_LINKED_COMMANDRATE); ROR_ASSERT(result >= 0);
    result = engine->RegisterEnumValue("ModulationSources", "SS_MOD_MUSIC_VOLUME", SS_MOD_MUSIC_VOLUME); ROR_ASSERT(result >= 0);

    // class SoundScriptTemplate
    SoundScriptTemplate::RegisterRefCountingObject(engine, "SoundScriptTemplateClass");
    SoundScriptTemplatePtr::RegisterRefCountingObjectPtr(engine, "SoundScriptTemplateClassPtr", "SoundScriptTemplateClass");

    result = engine->RegisterObjectMethod("SoundScriptTemplateClass", "int getNumSounds()", asMETHOD(SoundScriptTemplate, getNumSounds), asCALL_THISCALL); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectMethod("SoundScriptTemplateClass", "string getSoundName()", asMETHOD(SoundScriptTemplate, getSoundName), asCALL_THISCALL); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectMethod("SoundScriptTemplateClass", "float getSoundPitch()", asMETHOD(SoundScriptTemplate, getSoundPitch), asCALL_THISCALL); ROR_ASSERT(result >= 0);

    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "string name", offsetof(SoundScriptTemplate, name)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "string file_name", offsetof(SoundScriptTemplate, file_name)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "string group_name", offsetof(SoundScriptTemplate, group_name)); ROR_ASSERT(result >= 0);

    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "bool base_template", offsetof(SoundScriptTemplate, base_template)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "bool has_start_sound", offsetof(SoundScriptTemplate, has_start_sound)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "bool has_stop_sound", offsetof(SoundScriptTemplate, has_stop_sound)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "bool unpitchable", offsetof(SoundScriptTemplate, unpitchable)); ROR_ASSERT(result >= 0);

    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float gain_multiplier", offsetof(SoundScriptTemplate, gain_multiplier)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float gain_offset", offsetof(SoundScriptTemplate, gain_offset)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float gain_square", offsetof(SoundScriptTemplate, gain_square)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "ModulationSources gain_source", offsetof(SoundScriptTemplate, gain_source)); ROR_ASSERT(result >= 0);

    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float pitch_multiplier", offsetof(SoundScriptTemplate, pitch_multiplier)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float pitch_offset", offsetof(SoundScriptTemplate, pitch_offset)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float pitch_square", offsetof(SoundScriptTemplate, pitch_square)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "ModulationSources pitch_source", offsetof(SoundScriptTemplate, pitch_source)); ROR_ASSERT(result >= 0);

    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "string start_sound_name", offsetof(SoundScriptTemplate, start_sound_name)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float start_sound_pitch", offsetof(SoundScriptTemplate, start_sound_pitch)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "string stop_sound_name", offsetof(SoundScriptTemplate, stop_sound_name)); ROR_ASSERT(result >= 0);
    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "float stop_sound_pitch", offsetof(SoundScriptTemplate, stop_sound_pitch)); ROR_ASSERT(result >= 0);

    result = engine->RegisterObjectProperty("SoundScriptTemplateClass", "SoundTriggers trigger_source", offsetof(SoundScriptTemplate, trigger_source)); ROR_ASSERT(result >= 0);
}