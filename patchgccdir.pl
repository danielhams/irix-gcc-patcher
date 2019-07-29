#!/usr/bin/env perl

use lib ".";

use File::Find;
use File::Basename;
use File::Copy;
use DidbsUtils;

my $dest_dir = $ARGV[0];

print "Output to $dest_dir\n";

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

exit;

sub _wanted {
    return if ! -e;
    my ($dirs, $files) = @_;

    push( @$dirs, $File::Find::name ) if -d;
    push( @$files, $File::Find::name ) if ! -d;
}
