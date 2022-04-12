<?php

/**
 * @generate-function-entries
 * @generate-legacy-arginfo
 */

/* ccsid.c */
function ibmi_get_job_ccsid(): int {}

function ibmi_get_pase_ccsid(): int {}

/* systemcl.c */
/**
 * @param array $output
 */
function ibmi_cl_exec(string $command, int $flags = 0, &$output = null): string|false {}

function ibmi_cl_system(string $command, int $flags = 0): string|false {}

function ibmi_cl_passthru(string $command, int $flags = 0): ?bool {}

/* files.c */
/**
 * @return array|false
 */
function ibmi_stat(string $filename) {}

/* xmlservice.c */
function ibmi_xmlservice(string $input, string $ctl = "", string $ipc = ""): string|false {}
