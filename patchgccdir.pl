#!/usr/bin/env perl

use lib ".";

use File::Find;
use File::Basename;
use File::Copy;
use DidbsUtils;

my $dest_dir = $ARGV[0];

if( length($dest_dir) == 0 ) {
    print "Destination directory for patch missing.\n";
    exit 1;
}


print "Output to $dest_dir\n";

my $expected_configure_ac_file = "$dest_dir/configure.ac";

if( ! -e $expected_configure_ac_file )
{
    print "Cannot find expected configure.ac file at $expected_configure_ac_file\n";
    exit 1;
}

my $direct_copy_source = "directcopyfiles";
my $dirs = [];
my $files = [];
my $wanted = sub { _wanted($dirs,$files) };

find($wanted, $direct_copy_source);
#print "Files: @$files\n";
#print "Dirs: @$dirs\n";

my $filestubs = [];
for my $fullrelfile (@$files)
{
#    print "Fullrelfile is $fullrelfile\n";
    my $filestub = substr($fullrelfile,length($direct_copy_source)+1);
#    print "Doing $filestub\n";
    push( @$filestubs, $filestub );
}

# Loop copying over direct copy files
for my $filestub (@$filestubs)
{
    my $dest_fn = $dest_dir . "/" . $filestub;
    my $source_fn = $direct_copy_source . "/" . $filestub;
    
    my $dest_fn_dir = dirname($dest_fn);
    my $source_fn_dir = dirname($source_fn);
#    print "df=$dest_fn sf=$source_fn dfd=$dest_fn_dir sfd=$source_fn_dir\n";

    if( ! -e $dest_fn_dir ) {
	mkdirp($dest_fn_dir);
    }

    if( -e $dest_fn ) {
	my $backup_fn = $dest_fn . ".backup";
	copy($dest_fn,$backup_fn);
    }
    
    copy($source_fn,$dest_fn);
}

my $manual_edit_source = "manualeditfiles";
$dirs = [];
$files = [];
$wanted = sub { _wanted($dirs,$files) };
find($wanted, $manual_edit_source);

my $filestubs = [];
for my $fullrelfile (@$files)
{
#    print "Fullrelfile is $fullrelfile\n";
    my $filestub = substr($fullrelfile,length($manual_edit_source)+1);
#    print "Doing $filestub\n";
    push( @$filestubs, $filestub );
}

# Loop notifying that files require manual edits / diffs
for my $filestub (@$filestubs)
{
    my $dest_fn = $dest_dir . "/" . $filestub;
    my $source_fn = $manual_edit_source . "/" . $filestub;
    
    my $dest_fn_dir = dirname($dest_fn);
    my $source_fn_dir = dirname($source_fn);
#    print "df=$dest_fn sf=$source_fn dfd=$dest_fn_dir sfd=$source_fn_dir\n";

    if( ! -e $dest_fn_dir ) {
	mkdirp($dest_fn_dir);
    }

    if( -e $dest_fn ) {
	my $backup_fn = $dest_fn . ".backup";
	copy($dest_fn,$backup_fn);
    }
    
    print "You must manually edit $dest_fn\n";
}

exit;

sub _wanted {
    return if ! -e;
    my ($dirs, $files) = @_;

    push( @$dirs, $File::Find::name ) if -d;
    push( @$files, $File::Find::name ) if ! -d;
}
