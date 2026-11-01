/*
 * HarmonicField.h - harmonic fields (scales/modes, diatonic chords, key mapping)
 *
 * This file is part of LMMS - https://lmms.io
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */

#ifndef LMMS_HARMONIC_FIELD_H
#define LMMS_HARMONIC_FIELD_H

// This header only depends on the C++ standard library so that the musical
// logic can be unit tested without Qt.  All strings are UTF-8.

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

namespace lmms::harmonic
{

//! One harmonic field (scale / mode): its name and the semitone steps from the tonic.
struct Mode
{
	const char* family;
	const char* name;
	std::vector<int> steps;

	int size() const { return static_cast<int>(steps.size()); }
};

//! Every harmonic field offered in the piano roll.
inline const std::vector<Mode>& modes()
{
	static const std::vector<Mode> table =
	{
		// ---- Escala maior e seus modos (modos gregos) ----
		{ "Modos gregos", "Maior (Jônio)",            { 0, 2, 4, 5, 7, 9, 11 } },
		{ "Modos gregos", "Dórico",                   { 0, 2, 3, 5, 7, 9, 10 } },
		{ "Modos gregos", "Frígio",                   { 0, 1, 3, 5, 7, 8, 10 } },
		{ "Modos gregos", "Lídio",                    { 0, 2, 4, 6, 7, 9, 11 } },
		{ "Modos gregos", "Mixolídio",                { 0, 2, 4, 5, 7, 9, 10 } },
		{ "Modos gregos", "Menor natural (Eólio)",    { 0, 2, 3, 5, 7, 8, 10 } },
		{ "Modos gregos", "Lócrio",                   { 0, 1, 3, 5, 6, 8, 10 } },

		// ---- Menor harmônica e seus modos ----
		{ "Menor harmônica", "Menor harmônica",                 { 0, 2, 3, 5, 7, 8, 11 } },
		{ "Menor harmônica", "Lócrio ♮6",                       { 0, 1, 3, 5, 6, 9, 10 } },
		{ "Menor harmônica", "Jônio #5",                        { 0, 2, 4, 5, 8, 9, 11 } },
		{ "Menor harmônica", "Dórico #4 (Romeno)",              { 0, 2, 3, 6, 7, 9, 10 } },
		{ "Menor harmônica", "Frígio dominante (Frígio ♮3)",    { 0, 1, 4, 5, 7, 8, 10 } },
		{ "Menor harmônica", "Lídio #2",                        { 0, 3, 4, 6, 7, 9, 11 } },
		{ "Menor harmônica", "Super Lócrio bb7 (Ultralócrio)",  { 0, 1, 3, 4, 6, 8, 9 } },

		// ---- Menor melódica e seus modos ----
		{ "Menor melódica", "Menor melódica",                   { 0, 2, 3, 5, 7, 9, 11 } },
		{ "Menor melódica", "Dórico b2 (Frígio ♮6)",            { 0, 1, 3, 5, 7, 9, 10 } },
		{ "Menor melódica", "Lídio aumentado",                  { 0, 2, 4, 6, 8, 9, 11 } },
		{ "Menor melódica", "Lídio dominante (Lídio b7)",       { 0, 2, 4, 6, 7, 9, 10 } },
		{ "Menor melódica", "Mixolídio b6",                     { 0, 2, 4, 5, 7, 8, 10 } },
		{ "Menor melódica", "Lócrio ♮2 (Semilócrio)",           { 0, 2, 3, 5, 6, 8, 10 } },
		{ "Menor melódica", "Alterada (Super Lócrio)",          { 0, 1, 3, 4, 6, 8, 10 } },

		// ---- Maior harmônica e seus modos ----
		{ "Maior harmônica", "Maior harmônica",                 { 0, 2, 4, 5, 7, 8, 11 } },
		{ "Maior harmônica", "Dórico b5",                       { 0, 2, 3, 5, 6, 9, 10 } },
		{ "Maior harmônica", "Frígio b4",                       { 0, 1, 3, 4, 7, 8, 10 } },
		{ "Maior harmônica", "Lídio b3",                        { 0, 2, 3, 6, 7, 9, 11 } },
		{ "Maior harmônica", "Mixolídio b2",                    { 0, 1, 4, 5, 7, 9, 10 } },
		{ "Maior harmônica", "Lídio aumentado #2",              { 0, 3, 4, 6, 8, 9, 11 } },
		{ "Maior harmônica", "Lócrio bb7",                      { 0, 1, 3, 5, 6, 8, 9 } },

		// ---- Dupla harmônica (bizantina / árabe) e modos ----
		{ "Dupla harmônica", "Dupla harmônica maior (Bizantina)", { 0, 1, 4, 5, 7, 8, 11 } },
		{ "Dupla harmônica", "Lídio #2 #6",                       { 0, 3, 4, 6, 7, 10, 11 } },
		{ "Dupla harmônica", "Ultra-Frígio",                      { 0, 1, 3, 4, 7, 8, 9 } },
		{ "Dupla harmônica", "Húngara menor (Dupla harmônica menor)", { 0, 2, 3, 6, 7, 8, 11 } },
		{ "Dupla harmônica", "Oriental",                          { 0, 1, 4, 5, 6, 9, 10 } },
		{ "Dupla harmônica", "Jônio #2 #5",                       { 0, 3, 4, 5, 8, 9, 11 } },
		{ "Dupla harmônica", "Lócrio bb3 bb7",                    { 0, 1, 2, 5, 6, 8, 9 } },

		// ---- Outras escalas heptatônicas ----
		{ "Outras (7 notas)", "Húngara maior",       { 0, 3, 4, 6, 7, 9, 10 } },
		{ "Outras (7 notas)", "Napolitana maior",    { 0, 1, 3, 5, 7, 9, 11 } },
		{ "Outras (7 notas)", "Napolitana menor",    { 0, 1, 3, 5, 7, 8, 11 } },
		{ "Outras (7 notas)", "Persa",               { 0, 1, 4, 5, 6, 8, 11 } },
		{ "Outras (7 notas)", "Enigmática",          { 0, 1, 4, 6, 8, 10, 11 } },

		// ---- Escalas simétricas, pentatônicas e outras ----
		{ "Simétricas", "Tons inteiros (6 notas)",           { 0, 2, 4, 6, 8, 10 } },
		{ "Simétricas", "Diminuta tom-semitom (8 notas)",    { 0, 2, 3, 5, 6, 8, 9, 11 } },
		{ "Simétricas", "Diminuta semitom-tom (8 notas)",    { 0, 1, 3, 4, 6, 7, 9, 10 } },
		{ "Simétricas", "Aumentada (6 notas)",               { 0, 3, 4, 7, 8, 11 } },
		{ "Pentatônicas e outras", "Pentatônica maior",      { 0, 2, 4, 7, 9 } },
		{ "Pentatônicas e outras", "Pentatônica menor",      { 0, 3, 5, 7, 10 } },
		{ "Pentatônicas e outras", "Blues menor (6 notas)",  { 0, 3, 5, 6, 7, 10 } },
		{ "Pentatônicas e outras", "Blues maior (6 notas)",  { 0, 2, 3, 4, 7, 9 } },
		{ "Pentatônicas e outras", "Hirajoshi",              { 0, 2, 3, 7, 8 } },
		{ "Pentatônicas e outras", "In Sen",                 { 0, 1, 5, 7, 10 } },
		{ "Pentatônicas e outras", "Bebop maior (8 notas)",  { 0, 2, 4, 5, 7, 8, 9, 11 } },
		{ "Pentatônicas e outras", "Bebop dominante (8 notas)", { 0, 2, 4, 5, 7, 9, 10, 11 } },
		{ "Pentatônicas e outras", "Cromática (12 notas)",   { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 } },
	};
	return table;
}

//! Text shown in the combo box for a mode, e.g. "Modos gregos: Dórico".
inline std::string modeLabel(const Mode& m)
{
	return std::string(m.family) + ": " + m.name;
}

//! Chord sizes the user can pick for the keys.
inline const std::vector<std::string>& chordSizeLabels()
{
	static const std::vector<std::string> labels =
	{
		"Só a nota", "Tríade (3 notas)", "Tétrade (4 notas, com 7ª)", "Pentade (5 notas, com 9ª)"
	};
	return labels;
}

//! Number of notes of the chord for a chord-size index (0..3).
inline int chordNoteCount(int chordSizeIndex)
{
	static const int counts[] = { 1, 3, 4, 5 };
	return counts[std::clamp(chordSizeIndex, 0, 3)];
}

// ---------------------------------------------------------------------------
// Basic arithmetic
// ---------------------------------------------------------------------------

inline int floorDiv(int a, int b)
{
	int q = a / b;
	if ((a % b != 0) && ((a < 0) != (b < 0))) { --q; }
	return q;
}

inline int floorMod(int a, int b) { return a - floorDiv(a, b) * b; }

//! Semitones above the tonic of the scale note with the given (unbounded) index.
//! Index 0 is the tonic, index N is the tonic one octave up, -1 is the note below the tonic...
inline int semitoneOfIndex(const Mode& m, int index)
{
	const int n = m.size();
	return floorDiv(index, n) * 12 + m.steps[floorMod(index, n)];
}

//! Offsets (in semitones, from the chord root) of the notes of the diatonic chord
//! built by stacking thirds (every other scale note) on the given degree.
inline std::vector<int> chordOffsets(const Mode& m, int degree, int noteCount)
{
	std::vector<int> out;
	const int root = semitoneOfIndex(m, degree);
	for (int k = 0; k < noteCount; ++k)
	{
		out.push_back(semitoneOfIndex(m, degree + 2 * k) - root);
	}
	return out;
}

// ---------------------------------------------------------------------------
// Note names (correct spelling for 7-note scales: C D E F G A B, F# G# A# B C# D# E#, ...)
// ---------------------------------------------------------------------------

inline std::string accidentalString(int acc)
{
	return acc >= 0 ? std::string(acc, '#') : std::string(-acc, 'b');
}

inline std::vector<std::string> spellDegrees(const Mode& m, int tonicPc)
{
	static const char* const letters[7] = { "C", "D", "E", "F", "G", "A", "B" };
	static const int basePc[7] = { 0, 2, 4, 5, 7, 9, 11 };
	struct Cand { int letter; int acc; };

	const int n = m.size();
	std::vector<std::string> names(n);
	tonicPc = floorMod(tonicPc, 12);

	if (n == 7)
	{
		// tonic spellings, preferred first
		static const std::vector<Cand> cands[12] =
		{
			{ {0, 0} }, { {1, -1}, {0, 1} }, { {1, 0} }, { {2, -1}, {1, 1} },
			{ {2, 0} }, { {3, 0} }, { {3, 1}, {4, -1} }, { {4, 0} },
			{ {5, -1}, {4, 1} }, { {5, 0} }, { {6, -1}, {5, 1} }, { {6, 0} }
		};

		int bestCost = 1 << 30;
		for (const Cand& c : cands[tonicPc])
		{
			int cost = 0;
			std::vector<std::string> tmp(n);
			for (int i = 0; i < n; ++i)
			{
				const int letter = (c.letter + i) % 7;
				const int target = (tonicPc + m.steps[i]) % 12;
				const int acc = ((target - basePc[letter] + 18) % 12) - 6;
				cost += std::abs(acc) + (std::abs(acc) > 1 ? 100 : 0);
				tmp[i] = std::string(letters[letter]) + accidentalString(acc);
			}
			if (cost < bestCost) { bestCost = cost; names = tmp; }
		}
		return names;
	}

	// Non 7-note scales: plain sharp or flat names
	static const char* const sharp[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
	static const char* const flat[12]  = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };
	const bool useFlats = tonicPc == 1 || tonicPc == 3 || tonicPc == 5 || tonicPc == 8 || tonicPc == 10;
	for (int i = 0; i < n; ++i)
	{
		const int pc = (tonicPc + m.steps[i]) % 12;
		names[i] = useFlats ? flat[pc] : sharp[pc];
	}
	return names;
}

// ---------------------------------------------------------------------------
// Chord quality / names
// ---------------------------------------------------------------------------

struct Quality
{
	const char* signature;  //!< semitones from the root, e.g. "0,4,7"
	const char* suffix;     //!< chord-symbol suffix (cifra), e.g. "m7"
	const char* romanSuffix;//!< suffix used after the roman numeral
	bool lowerCase;         //!< roman numeral in lower case (minor third)
};

inline const Quality* findQuality(const std::vector<int>& offsets)
{
	static const Quality table[] =
	{
		// triads
		{ "0,4,7", "", "", false },
		{ "0,3,7", "m", "", true },
		{ "0,3,6", "dim", "dim", true },
		{ "0,4,8", "aug", "aug", false },
		{ "0,2,7", "sus2", "sus2", false },
		{ "0,5,7", "sus4", "sus4", false },
		{ "0,4,6", "(b5)", "(b5)", false },
		// seventh chords
		{ "0,4,7,11", "7M", "7M", false },
		{ "0,4,7,10", "7", "7", false },
		{ "0,3,7,10", "m7", "7", true },
		{ "0,3,6,10", "m7(b5)", "7(b5)", true },
		{ "0,3,6,9", "dim7", "dim7", true },
		{ "0,3,7,11", "m(7M)", "(7M)", true },
		{ "0,4,8,11", "7M(#5)", "7M(#5)", false },
		{ "0,4,8,10", "7(#5)", "7(#5)", false },
		{ "0,4,6,10", "7(b5)", "7(b5)", false },
		{ "0,4,6,11", "7M(b5)", "7M(b5)", false },
		{ "0,3,6,11", "dim(7M)", "dim(7M)", true },
		{ "0,3,8,10", "m7(b13)", "7(b13)", true },
		{ "0,4,7,9", "6", "6", false },
		{ "0,3,7,9", "m6", "6", true },
		{ "0,2,7,10", "7sus2", "7sus2", false },
		{ "0,5,7,10", "7sus4", "7sus4", false },
		{ "0,2,7,11", "7Msus2", "7Msus2", false },
		{ "0,5,7,11", "7Msus4", "7Msus4", false },
	};

	std::string sig;
	for (std::size_t i = 0; i < offsets.size(); ++i)
	{
		if (i) { sig += ','; }
		sig += std::to_string(offsets[i]);
	}
	for (const Quality& q : table)
	{
		if (sig == q.signature) { return &q; }
	}
	return nullptr;
}

//! Quality of the chord on `degree`; for 5-note chords the quality of its first four notes.
inline const Quality* degreeQuality(const Mode& m, int degree, int noteCount)
{
	const int basis = std::min(noteCount, 4);
	return findQuality(chordOffsets(m, degree, basis));
}

//! Chord symbol (cifra) of the chord on `degree`, e.g. "Dm", "G7", "Bdim", "C7M", "G9".
inline std::string chordLabel(const Mode& m, int tonicPc, int degree, int noteCount)
{
	const auto names = spellDegrees(m, tonicPc);
	const std::string& root = names[floorMod(degree, m.size())];
	if (noteCount <= 1) { return root; }

	const Quality* q = degreeQuality(m, degree, noteCount);
	if (!q)
	{
		// Unnamed stack of thirds: show the intervals above the root, e.g. "D(0-3-8)"
		std::string intervals;
		for (int off : chordOffsets(m, degree, std::min(noteCount, 4)))
		{
			if (!intervals.empty()) { intervals += '-'; }
			intervals += std::to_string(off);
		}
		return root + "(" + intervals + ")";
	}
	std::string suffix = q->suffix;
	if (noteCount >= 5)
	{
		if (suffix == "7") { suffix = "9"; }
		else if (suffix == "m7") { suffix = "m9"; }
		else if (suffix == "7M") { suffix = "7M(9)"; }
		else { suffix += "(9)"; }
	}
	return root + suffix;
}

//! Roman numeral (7-note scales) or degree number (other scales), e.g. "ii", "V7", "bVII", "viidim".
inline std::string degreeLabel(const Mode& m, int degree, int noteCount)
{
	degree = floorMod(degree, m.size());
	if (m.size() != 7) { return std::to_string(degree + 1); }

	static const char* const numerals[7] = { "I", "II", "III", "IV", "V", "VI", "VII" };
	static const int majorSteps[7] = { 0, 2, 4, 5, 7, 9, 11 };

	std::string prefix;
	const int diff = m.steps[degree] - majorSteps[degree];
	if (diff < 0) { prefix = std::string(-diff, 'b'); }
	else if (diff > 0) { prefix = std::string(diff, '#'); }

	if (noteCount <= 1) { return prefix + std::to_string(degree + 1); }

	const Quality* q = degreeQuality(m, degree, noteCount);
	std::string numeral = numerals[degree];
	std::string suffix;
	bool lower = false;
	if (q)
	{
		lower = q->lowerCase;
		suffix = q->romanSuffix;
	}
	else
	{
		const auto off = chordOffsets(m, degree, 2);
		lower = off.size() > 1 && off[1] == 3;
	}
	if (lower)
	{
		std::transform(numeral.begin(), numeral.end(), numeral.begin(),
			[](unsigned char c) { return static_cast<char>(std::tolower(c)); });
	}
	if (noteCount >= 5)
	{
		if (suffix == "7") { suffix = "9"; }
		else { suffix += "(9)"; }
	}
	return prefix + numeral + suffix;
}

//! Name of the field, e.g. "C Maior (Jônio)".
inline std::string fieldTitle(const Mode& m, int tonicPc)
{
	return spellDegrees(m, tonicPc)[0] + " " + m.name;
}

//! One-line description of the whole field with its chords, e.g.
//! "C Maior (Jônio):  I C  |  ii Dm  |  iii Em  | ..."
inline std::string fieldSummary(const Mode& m, int tonicPc, int noteCount)
{
	std::string s = fieldTitle(m, tonicPc) + ":  ";
	for (int d = 0; d < m.size(); ++d)
	{
		if (d) { s += "  |  "; }
		s += degreeLabel(m, d, noteCount) + " " + chordLabel(m, tonicPc, d, noteCount);
	}
	return s;
}

// ---------------------------------------------------------------------------
// Piano roll helpers
// ---------------------------------------------------------------------------

//! Piano-roll keys (0..numKeys-1) that belong to the field, highest first.
inline std::vector<int> fieldKeys(const Mode& m, int tonicPc, int numKeys)
{
	std::vector<int> out;
	for (int key = numKeys - 1; key >= 0; --key)
	{
		const int rel = floorMod(key - tonicPc, 12);
		if (std::find(m.steps.begin(), m.steps.end(), rel) != m.steps.end()) { out.push_back(key); }
	}
	return out;
}

//! Degree (0-based) of a piano-roll key within the field, or -1 if it is not part of it.
inline int degreeOfKey(const Mode& m, int tonicPc, int key)
{
	const int rel = floorMod(key - tonicPc, 12);
	for (int i = 0; i < m.size(); ++i)
	{
		if (m.steps[i] == rel) { return i; }
	}
	return -1;
}

// Keyboard layout: 4 rows (Z row, A row, Q row, number row) of 10 keys each.
// Each row is one octave higher than the previous one.
constexpr int KeyboardColumns = 10;
constexpr int KeyboardRows = 4;
constexpr int KeyboardSlots = KeyboardColumns * KeyboardRows;

//! Scale index played by a keyboard slot (row * 10 + column).
//! A row spans one octave of the scale (or 10 notes if the scale has more than 10).
inline int scaleIndexForSlot(const Mode& m, int slot)
{
	const int row = slot / KeyboardColumns;
	const int col = slot % KeyboardColumns;
	return row * std::min(m.size(), KeyboardColumns) + col;
}

//! Piano-roll key of the tonic of the lowest row. `baseKey` is the key of the C of the lowest row's octave.
inline int tonicKey(int tonicPc, int baseKey)
{
	tonicPc = floorMod(tonicPc, 12);
	return baseKey + (tonicPc > 6 ? tonicPc - 12 : tonicPc);
}

//! All piano-roll keys that sound when `slot` is pressed (root first). Keys outside 0..numKeys-1 are dropped.
inline std::vector<int> keysForSlot(const Mode& m, int tonicPc, int baseKey, int slot, int noteCount, int numKeys)
{
	std::vector<int> out;
	if (slot < 0 || slot >= KeyboardSlots) { return out; }

	const int index = scaleIndexForSlot(m, slot);
	const int root = tonicKey(tonicPc, baseKey) + semitoneOfIndex(m, index);
	const int degree = floorMod(index, m.size());
	for (int offset : chordOffsets(m, degree, noteCount))
	{
		const int key = root + offset;
		if (key >= 0 && key < numKeys) { out.push_back(key); }
	}
	return out;
}

} // namespace lmms::harmonic

#endif // LMMS_HARMONIC_FIELD_H
