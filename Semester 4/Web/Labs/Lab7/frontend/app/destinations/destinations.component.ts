// src/app/destinations/destinations.component.ts
import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { HttpClient, HttpParams } from '@angular/common/http';
import { FormsModule } from '@angular/forms';
import { RouterModule } from '@angular/router';

@Component({
  selector: 'app-destinations',
  standalone: true,
  imports: [CommonModule, FormsModule, RouterModule],
  templateUrl: './destinations.component.html',
  styleUrls: ['./destinations.component.css']
})
export class DestinationsComponent implements OnInit {
  destinations: any[] = [];
  countryFilter: string = '';
  currentPage: number = 1;
  totalPages: number = 1;
  pageInfo: string = 'Page 1';

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.fetchDestinations();
  }

  fetchDestinations() {
    const params = new HttpParams()
      .set('country', this.countryFilter)
      .set('page', this.currentPage.toString());

    this.http.get<any>('http://localhost/vacation_app/get_destinations.php', { params })
      .subscribe(data => {
        this.destinations = data.destinations;
        this.currentPage = data.page;
        this.totalPages = data.totalPages;
        this.pageInfo = `Page ${data.page} of ${data.totalPages}`;
      });
  }

  deleteDestination(id: number) {
    if (confirm('Are you sure you want to delete this destination?')) {
      const formData = new FormData();
      formData.append('id', id.toString());

      this.http.post<any>('http://localhost/vacation_app/delete_destination.php', formData)
        .subscribe(response => {
          if (response.success) {
            this.fetchDestinations();
          } else {
            alert('Failed to delete destination');
          }
        });
    }
  }

  editDestination(id: number) {
    window.location.href = `http://localhost/vacation_app/edit_destination.php?id=${id}`;
  } 

  nextPage() {
    if (this.currentPage < this.totalPages) {
      this.currentPage++;
      this.fetchDestinations();
    }
  }

  prevPage() {
    if (this.currentPage > 1) {
      this.currentPage--;
      this.fetchDestinations();
    }
  }

  onFilterChange() {
    this.currentPage = 1;
    this.fetchDestinations();
  }
}
