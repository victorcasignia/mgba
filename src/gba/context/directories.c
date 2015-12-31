/* Copyright (c) 2013-2015 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#include "directories.h"

#include "util/vfs.h"

void GBADirectorySetInit(struct GBADirectorySet* dirs) {
	dirs->base = 0;
	dirs->archive = 0;
	dirs->save = 0;
	dirs->patch = 0;
	dirs->state = 0;
	dirs->screenshot = 0;
}

void GBADirectorySetDeinit(struct GBADirectorySet* dirs) {
	GBADirectorySetDetachBase(dirs);

	if (dirs->archive) {
		dirs->archive->close(dirs->archive);
		dirs->archive = 0;
	}

	if (dirs->save) {
		dirs->save->close(dirs->save);
		dirs->save = 0;
	}

	if (dirs->patch) {
		dirs->patch->close(dirs->patch);
		dirs->patch = 0;
	}

	if (dirs->state) {
		dirs->state->close(dirs->state);
		dirs->state = 0;
	}

	if (dirs->screenshot) {
		dirs->screenshot->close(dirs->screenshot);
		dirs->screenshot = 0;
	}
}

void GBADirectorySetAttachBase(struct GBADirectorySet* dirs, struct VDir* base) {
	dirs->base = base;
	if (!dirs->save) {
		dirs->save = dirs->base;
	}
	if (!dirs->patch) {
		dirs->patch = dirs->base;
	}
	if (!dirs->state) {
		dirs->state = dirs->base;
	}
	if (!dirs->screenshot) {
		dirs->screenshot = dirs->base;
	}
}

void GBADirectorySetDetachBase(struct GBADirectorySet* dirs) {
	if (dirs->save == dirs->base) {
		dirs->save = 0;
	}
	if (dirs->patch == dirs->base) {
		dirs->patch = 0;
	}
	if (dirs->state == dirs->base) {
		dirs->state = 0;
	}
	if (dirs->screenshot == dirs->base) {
		dirs->screenshot = 0;
	}

	if (dirs->base) {
		dirs->base->close(dirs->base);
		dirs->base = 0;
	}
}

struct VFile* GBADirectorySetOpenPath(struct GBADirectorySet* dirs, const char* path, bool (*filter)(struct VFile*)) {
	dirs->archive = VDirOpenArchive(path);
	struct VFile* file;
	if (dirs->archive) {
		file = VDirFindFirst(dirs->archive, filter);
		if (!file) {
			dirs->archive->close(dirs->archive);
			dirs->archive = 0;
		}
	} else {
		file = VFileOpen(path, O_RDONLY);
		if (!filter(file)) {
			file->close(file);
			file = 0;
		}
	}
	return file;
}
